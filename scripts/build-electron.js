'use strict';

const { spawnSync } = require('child_process');
const fs = require('fs');
const path = require('path');

function readElectronVersion() {
	const fromEnv = process.env.npm_config_target || process.env.ELECTRON_VERSION;
	if (fromEnv) return fromEnv.replace(/^v/, '');

	const argIdx = process.argv.findIndex(a => a === '--target');
	if (argIdx !== -1 && process.argv[argIdx + 1]) {
		return process.argv[argIdx + 1].replace(/^v/, '');
	}

	const candidates = [
		path.join(process.cwd(), 'node_modules', 'electron', 'package.json'),
		path.join(__dirname, '..', '..', 'electron', 'package.json'),
		path.join(__dirname, '..', '..', '..', 'electron', 'package.json')
	];

	for (const candidate of candidates) {
		try {
			const pkg = JSON.parse(fs.readFileSync(candidate, 'utf8'));
			if (pkg.version) return pkg.version.replace(/^v/, '');
		} catch (_) {
			/* try next */
		}
	}

	console.error(
		'windows-iap-wrapper: could not resolve Electron version. Pass --target <version> or set ELECTRON_VERSION.'
	);
	process.exit(1);
}

function resolveNodeGyp() {
	try {
		return require.resolve('node-gyp/bin/node-gyp.js');
	} catch (_) {
		return 'node-gyp';
	}
}

if (process.platform !== 'win32') {
	console.log('windows-iap-wrapper: Electron native build is Windows-only; skipping on', process.platform);
	process.exit(0);
}

const target = readElectronVersion();
const arch = process.env.npm_config_arch || process.arch;
const gypArgs = [
	'rebuild',
	`--target=${target}`,
	'--runtime=electron',
	`--arch=${arch}`,
	'--dist-url=https://electronjs.org/headers',
	'--release'
];

console.log('windows-iap-wrapper: building for Electron', target, `(${arch})`);

const nodeGyp = resolveNodeGyp();
const args = nodeGyp.endsWith('.js') ? [nodeGyp, ...gypArgs] : gypArgs;
const cmd = nodeGyp.endsWith('.js') ? process.execPath : nodeGyp;

const result = spawnSync(cmd, args, {
	stdio: 'inherit',
	shell: !nodeGyp.endsWith('.js'),
	cwd: path.join(__dirname, '..'),
	env: process.env
});

process.exit(result.status === null ? 1 : result.status);

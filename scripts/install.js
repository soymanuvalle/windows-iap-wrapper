'use strict';

const { spawnSync } = require('child_process');
const path = require('path');

if (process.platform !== 'win32') {
	console.log('windows-iap-wrapper: skipping native build on', process.platform);
	process.exit(0);
}

function resolveNodeGyp() {
	try {
		return require.resolve('node-gyp/bin/node-gyp.js');
	} catch (_) {
		return 'node-gyp';
	}
}

const nodeGyp = resolveNodeGyp();
const args = nodeGyp.endsWith('.js') ? [nodeGyp, 'rebuild'] : ['rebuild'];
const cmd = nodeGyp.endsWith('.js') ? process.execPath : nodeGyp;

const result = spawnSync(cmd, args, {
	stdio: 'inherit',
	shell: !nodeGyp.endsWith('.js'),
	cwd: path.join(__dirname, '..'),
	env: process.env
});

process.exit(result.status === null ? 1 : result.status);

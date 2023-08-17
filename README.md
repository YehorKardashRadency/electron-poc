# cpp-electron

An Electron application with React


## PPSDK
To use PPSDK we have to use static library and headers copied from the PPSDK installation directory.
There are multiple versions of static libs, this app is using `static/vs2017_x64/MT`.
To compile the C++ code you have to install Visual Studio Build Tools 2022 and node-gyp:

```bash
npm install -g node-gyp
```

Having done that you can compile the code:

```bash
node-gyp configure
node-gyp build
# to get rid of "Compiled against a different Node.js version" error
.\node_modules\.bin\electron-rebuild.cmd
```

## Recommended IDE Setup

- [VSCode](https://code.visualstudio.com/) + [ESLint](https://marketplace.visualstudio.com/items?itemName=dbaeumer.vscode-eslint) + [Prettier](https://marketplace.visualstudio.com/items?itemName=esbenp.prettier-vscode)

## Project Setup

### Install

```bash
$ npm install
```

### Development

```bash
$ npm run dev
```

### Build

```bash
# For windows
$ npm run build:win

# For macOS
$ npm run build:mac

# For Linux
$ npm run build:linux
```

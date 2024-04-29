## Fork, then clone

```
git clone git@github.com:<your-username>/simcity4-webinterface-plugin.git
```

### Visual Studio

* Install "Visual Studio 2022 Community Edition"

### Configure

In ```SC4WebInterface.vcxproj``` adjust

* ```<Command>xcopy "$(TargetPath)" "``` xcopy to your Sim City 4 plugin path

### Build

From the VS 2022 Developer Command Prompt, run

```
cd src/
msbuild .\SC4WebInterface.sln
```

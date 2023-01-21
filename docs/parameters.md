# Parameters of noedge.exe
### Default Parameters
`--offline jsonFile=<jsonfile>` - Allows noedge.exe to execute without any internet connection. Here `<jsonfile>` is the path of a jsonfile which contains list of search engines and their parameters. It should be format like [search.json](../search.json) or it wouldn't work properly.

`--online` - Allows noedge.exe to fetch files from this repo instead of locally.

`--recovery` - Lists all backups which was created by noedge.exe.
### Debug Parameters
Note: This is intended for advanced users. And those parameters might be removed into future released. All parameters will work after passing `--debug` parameter.  
Example: `noedge.exe --debug --upgrade true`  

`--upgrade <bool>` - This is used for whether noedge.exe will fresh install or not. If no value passed then it just switch the current configuration to opposite e.g. true to false, false to true.

`--seenlicense <bool>` - Show/Hide the license screen while executing noedge.exe. If not value passed then it switch the current configuration with the opposite one.

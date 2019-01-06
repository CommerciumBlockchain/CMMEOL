call :GET_CURRENT_DIR
cd %APPDATA%
IF NOT EXIST %APPDATA%\ZcashParams (
MKDIR %APPDATA%\ZcashParams
)

cd ZcashParams

REM This script downloads's files...

> j_download.vbs ECHO Set objWinHttp = CreateObject("WinHttp.WinHttpRequest.5.1")
>> j_download.vbs ECHO URL = "https://github.com/CommerciumBlockchain/CommerciumContinuum/releases/download/data/ZcashParams.zip"
>> j_download.vbs ECHO objWinHttp.open "GET", URL, False
>> j_download.vbs ECHO objWinHttp.send ""
>> j_download.vbs ECHO SaveBinaryData "%APPDATA%\ZcashParams.zip",objWinHttp.responseBody
>> j_download.vbs ECHO Function SaveBinaryData(FileName, Data)
>> j_download.vbs ECHO. 
>> j_download.vbs ECHO ' adTypeText for binary = 1
>> j_download.vbs ECHO Const adTypeText = 1
>> j_download.vbs ECHO Const adSaveCreateOverWrite = 2
>> j_download.vbs ECHO. 
>> j_download.vbs ECHO ' Create Stream object
>> j_download.vbs ECHO Dim BinaryStream
>> j_download.vbs ECHO Set BinaryStream = CreateObject("ADODB.Stream")
>> j_download.vbs ECHO. 
>> j_download.vbs ECHO ' Specify stream type - we want To save Data/string data.
>> j_download.vbs ECHO BinaryStream.Type = adTypeText
>> j_download.vbs ECHO. 
>> j_download.vbs ECHO ' Open the stream And write binary data To the object
>> j_download.vbs ECHO BinaryStream.Open
>> j_download.vbs ECHO BinaryStream.Write Data
>> j_download.vbs ECHO. 
>> j_download.vbs ECHO ' Save binary data To disk
>> j_download.vbs ECHO BinaryStream.SaveToFile FileName, adSaveCreateOverWrite
>> j_download.vbs ECHO.
>> j_download.vbs ECHO End Function

REM This script upzip's files...

> j_unzip.vbs ECHO '
>> j_unzip.vbs ECHO.
>> j_unzip.vbs ECHO ' Dim ArgObj, var1, var2
>> j_unzip.vbs ECHO Set ArgObj = WScript.Arguments
>> j_unzip.vbs ECHO.
>> j_unzip.vbs ECHO If (Wscript.Arguments.Count ^> 0) Then
>> j_unzip.vbs ECHO. var1 = ArgObj(0)
>> j_unzip.vbs ECHO Else
>> j_unzip.vbs ECHO. var1 = ""
>> j_unzip.vbs ECHO End if
>> j_unzip.vbs ECHO.
>> j_unzip.vbs ECHO If var1 = "" then
>> j_unzip.vbs ECHO. strFileZIP = "ZcashParams.zip"
>> j_unzip.vbs ECHO Else
>> j_unzip.vbs ECHO. strFileZIP = var1
>> j_unzip.vbs ECHO End if
>> j_unzip.vbs ECHO.
>> j_unzip.vbs ECHO 'The location of the zip file.
>> j_unzip.vbs ECHO REM Set WshShell = CreateObject("Wscript.Shell")
>> j_unzip.vbs ECHO REM CurDir = WshShell.ExpandEnvironmentStrings("%%cd%%")
>> j_unzip.vbs ECHO Dim sCurPath
>> j_unzip.vbs ECHO sCurPath = CreateObject("Scripting.FileSystemObject").GetAbsolutePathName(".")
>> j_unzip.vbs ECHO strZipFile = sCurPath ^& "\" ^& strFileZIP
>> j_unzip.vbs ECHO 'The folder the contents should be extracted to.
>> j_unzip.vbs ECHO outFolder = sCurPath ^& "\"
>> j_unzip.vbs ECHO.
>> j_unzip.vbs ECHO. WScript.Echo ( "Extracting file " ^& strFileZIP)
>> j_unzip.vbs ECHO.
>> j_unzip.vbs ECHO Set objShell = CreateObject( "Shell.Application" )
>> j_unzip.vbs ECHO Set objSource = objShell.NameSpace(strZipFile).Items()
>> j_unzip.vbs ECHO Set objTarget = objShell.NameSpace(outFolder)
>> j_unzip.vbs ECHO intOptions = 256
>> j_unzip.vbs ECHO objTarget.CopyHere objSource, intOptions
>> j_unzip.vbs ECHO.
>> j_unzip.vbs ECHO. WScrip.Echo ( "Extracted." )
>> j_unzip.vbs ECHO.
>> j_unzip.vbs ECHO ' This bit is for testing purposes
>> j_unzip.vbs ECHO REM Dim MyVar
>> j_unzip.vbs ECHO REM MyVar = MsgBox ( strZipFile, 65, "MsgBox Example"


cscript //B j_download.vbs
cscript //B j_unzip.vbs ZcashParams.zip

goto :EOF
:GET_CURRENT_DIR
pushd %~dp0
set THIS_DIR=%CD%
popd
goto :EOF

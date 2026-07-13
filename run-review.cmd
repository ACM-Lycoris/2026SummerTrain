@echo off
chcp 65001 >nul
cd /d "%~dp0"

py -3 main.py
if errorlevel 9009 (
    python main.py
)

set "exit_code=%errorlevel%"
echo.
if "%exit_code%"=="0" (
    echo Analysis finished. Open the newest Markdown file in reports.
) else (
    echo Analysis failed with exit code %exit_code%.
)
pause
exit /b %exit_code%

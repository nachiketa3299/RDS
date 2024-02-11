echo "RDS Doxygen Generator"

set "DOXYGEN=E:\doxygen\bin\doxygen.exe"
set "DOXYFILE=.\Doxyfile.config"

"%DOXYGEN%" "%DOXYFILE%"
set "INDEX_HTML=E:/OneDrive/Projects/CppProjects/RDS/docs/generated/html/index.html"

start file://"%INDEX_HTML%"
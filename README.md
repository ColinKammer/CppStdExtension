# CppStdExtension
The Standard library is sometimes missing something, or a complier doesn't support a library feature yet.

## Hookable funcions
Some headers in this library intenionally leave some symbols undefined. This allows the consumer to integrate it into his project, using his own implmentation (e.g. Assertions).

However one or more default implementations are provided in the hookImpl subdirectory. Select the coresponding cpp-file to your taste.
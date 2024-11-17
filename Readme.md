# Bewertet Aufgabe AES

## Allgemeine Aufgabenstellung

* Implementieren Sie die AES-Verschlüsselung.
* Ihre Implementierung sollte in der beigefügten Vagrant-Box lauffähig sein.
* Testen Sie Ihre Implementierung mit den beigefügten Testfällen.
* Geben Sie entweder ein Script zum kompilieren und ausführen Ihrer Implementierung oder ein entsprechendes CMake-File ab.
* Im Folgenden werden die einzelnen Teilaufgaben ausführlicher beschrieben.

## Aufgabenstellung

Checken Sie das Git-Repository aus:

```console
$ git clone https://github.com/bladewing/infosec-uebungen-graded-01.git
```

Die Datei ```aes.h``` enthält die Deklarationen der Funktionen, die Sie implementieren müssen. 
Diese sind bereits als Dummy-Funktionen in ```aes.c``` implementiert, sodass die Tests bereits kompilieren und laufen sollten. 
Zudem finden Sie in der Datei ```aes.c``` die **S-Box** und die **inverse S-Box**, die Sie für die Implementierung von AES benötigen.

Die Beschreibung der erwarteten Logik der geforderten Funktionen finden Sie in der ```aes.h```.
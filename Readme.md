# Bewertete Aufgabe AES

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

## Kompilieren

* Nutzen Sie die beigefügte Vagrant-Box, in dieser ist alles notwendige bereits installiert. Wenn Sie lokal auf Ihrem Rechner arbeiten, müssen Sie sicherstellen, dass Ihre Lösung in der Vagrant-Box kompilierbar ist.
* Nutzen Sie das beigefügte CMake-File zum Kompilieren. Sie müssen sich dazu im Verzeichnis \texttt{code} befinden.
  * Konfigurieren Sie die CMake-Datei mit dem Befehl 
  ```console
  $ cmake .
  ```
  * Kompilieren Sie das Projekt mit dem Befehl 
  ```console
  cmake --build .
  ```
  * Führen Sie Ihre Tests mit dem Befehl 
  ```console
  $ ctest --output-on-failure
  ```
  Dieser gibt Ihnen die Ausgabe der Tests aus, wenn diese fehlschlagen.

## Abgabe

Laden Sie Ihre Lösung im OPAL-Kurs hoch. Es werden Abgaben in den Sprachen C und C++ akzeptiert.

Laden Sie Ihre Lösung als ZIP-Datei hoch. Diese sollte die Struktur der Aufgabenstellung widerspiegeln. 

## Hilfreiche Hinweise

* Im Kurs wurde ein Buch bereitgestellt, dass die Implementierung von AES beschreibt. Nutzen Sie dieses Buch als Referenz.
* Unter https://www.cryptool.org/en/cto/aes-step-by-step finden Sie eine interaktive Implementierung von AES. Nutzen Sie diese, um Ihre Implementierung zu testen und Fehler zu verstehen.
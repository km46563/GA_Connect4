Bot do gry Connect4 oparty na Algorytmie Genetycznym
====================================================

### Konfiguracja pliku CMakeLists.txt

Do pliku należy dopisać następujące linie kodu, aby poprawnie skonfigurować logowanie chromosomów do pliku:

```cmake
configure_file(Config.h.in ${CMAKE_BINARY_DIR}/Config.h @ONLY)
```

oraz

```cmake
target_include_directories(
        ...
        ${CMAKE_BINARY_DIR}
        ...
)
```

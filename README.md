# shore-backend-wxwidgets

The wxWidgets peer backend for Shore. Build it after installing the
backend-neutral `shore` core and wxWidgets core/base components.

```cmake
find_package(shore-backend-wxwidgets CONFIG REQUIRED)
target_link_libraries(app PRIVATE shore-backend-wxwidgets::shore-backend-wxwidgets)
```

Construct the app with `shore::backend::wxwidgets::CreateBackend()`. The
repository contains a standalone CMake package, a vcpkg port under
`ports/shore-backend-wxwidgets`, and a Linux GitHub Actions build. Backend
implementation classes each have a private header under `src`.

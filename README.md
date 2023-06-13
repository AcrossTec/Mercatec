# Mercatec

## [Microsoft Interface Definition Language](https://learn.microsoft.com/en-us/windows/win32/midl/midl-start-page)

* [MIDL Data Types](https://learn.microsoft.com/en-us/windows/win32/midl/midl-data-types)

## Microsoft Interface Definition Language 3.0 Reference

* [Introduction to Microsoft Interface Definition Language 3.0](https://learn.microsoft.com/en-us/uwp/midl-3/intro)
  * [Types](https://learn.microsoft.com/en-us/uwp/midl-3/intro#types)
  * [Properties](https://learn.microsoft.com/en-us/uwp/midl-3/intro#properties)
  * [Methods](https://learn.microsoft.com/en-us/uwp/midl-3/intro#methods)
  * [Attributes](https://learn.microsoft.com/en-us/uwp/midl-3/intro#attributes)

* [Synthesizing interfaces (MIDL 3.0)](https://learn.microsoft.com/en-us/uwp/midl-3/synthesizing-interfaces)

* [Predefined attributes (MIDL 3.0)](https://learn.microsoft.com/en-us/uwp/midl-3/predefined-attributes)

* [Advanced topics, and shorthand](https://learn.microsoft.com/en-us/uwp/midl-3/advanced)

* [The various patterns for passing C-style arrays across the Windows Runtime ABI boundary](https://devblogs.microsoft.com/oldnewthing/20200205-00/?p=103398)

* [How do I save a C++/WinRT array_view as a com_array?](https://devblogs.microsoft.com/oldnewthing/20201106-00/?p=104427)

* [How can I produce a C-style array from a Windows Runtime asynchronous operation?](https://devblogs.microsoft.com/oldnewthing/20211203-00/?p=105999)

* [How can my C++/WinRT component pass a std::vector back to the caller?](https://devblogs.microsoft.com/oldnewthing/20211130-00/?p=105985)

* [Inside C++/WinRT: How does C++/WinRT represent ABI types?](https://devblogs.microsoft.com/oldnewthing/20200924-00/?p=104275)

* [How do I make a clone of a Windows Runtime vector in C++/WinRT?](https://devblogs.microsoft.com/oldnewthing/20191122-00/?p=103123/)

## C++/WinRT

* [Bonus operations for C++/WinRT iterators: The IIterator&lt;T&gt;](https://devblogs.microsoft.com/oldnewthing/20200930-00/?p=104321)

* [Bonus operations for C++/WinRT iterators: The IIterable&lt;T&gt;, and C++/WinRT collections](https://devblogs.microsoft.com/oldnewthing/20201001-00/?p=104325)

* [C++ coroutines: The lifetime of objects involved in the coroutine function](https://devblogs.microsoft.com/oldnewthing/20210412-00/?p=105078)

* WinRT Namespace
  * [winrt::static_lifetime marker struct (C++/WinRT)](https://learn.microsoft.com/en-us/uwp/cpp-ref-for-winrt/static-lifetime)

  * [winrt::array_view struct template (C++/WinRT)](https://learn.microsoft.com/en-us/uwp/cpp-ref-for-winrt/array-view)
  
  * [winrt::com_array struct template (C++/WinRT)](https://learn.microsoft.com/en-us/uwp/cpp-ref-for-winrt/com-array)
  
  * [winrt::observable_vector_base struct template (C++/WinRT)](https://learn.microsoft.com/en-us/uwp/cpp-ref-for-winrt/observable-vector-base)
  
  * [winrt::single_threaded_observable_vector function template (C++/WinRT)](https://learn.microsoft.com/en-us/uwp/cpp-ref-for-winrt/single-threaded-observable-vector)

	* [Collections with C++/WinRT](https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/collections)

## C/C++ projects and build systems in Visual Studio

* [Walkthrough: Create and use your own Dynamic Link Library (C++)](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170)

* [Walkthrough: Create and use a static library (C++)](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?view=msvc-170)

## [Authentication And User Identity](https://learn.microsoft.com/en-us/windows/uwp/security/authentication-and-user-identity)

* [Credential Locker](https://learn.microsoft.com/en-us/windows/uwp/security/credential-locker)

* [Windows Hello](https://learn.microsoft.com/en-us/windows/uwp/security/microsoft-passport)
  * [Create a Windows Hello login app](https://learn.microsoft.com/en-us/windows/uwp/security/microsoft-passport-login)
  * [Create a Windows Hello login service](https://learn.microsoft.com/en-us/windows/uwp/security/microsoft-passport-login-auth-service)

* [Cryptography](https://learn.microsoft.com/en-us/windows/uwp/security/cryptography)
  * [MACs, hashes, and signatures](https://learn.microsoft.com/en-us/windows/uwp/security/macs-hashes-and-signatures)

## [vcpkg is Now Included with Visual Studio](https://devblogs.microsoft.com/cppblog/vcpkg-is-now-included-with-visual-studio/)

* [vcpkg.json Reference](https://learn.microsoft.com/en-us/vcpkg/reference/vcpkg-json)

* [vcpkg-configuration.json Reference](https://learn.microsoft.com/en-us/vcpkg/reference/vcpkg-configuration-json)

* [Installing and Using Packages Example: SQLite](https://learn.microsoft.com/en-us/vcpkg/examples/installing-and-using-packages)

* [Manifest mode](https://learn.microsoft.com/en-us/vcpkg/users/manifests)

* [Manifest mode: CMake example](https://learn.microsoft.com/en-us/vcpkg/examples/manifest-mode-cmake)

* [Using Registries](https://learn.microsoft.com/en-us/vcpkg/users/registries)

* Packaging GitHub repos examples
  * [Packaging GitHub repos example: libogg](https://learn.microsoft.com/en-us/vcpkg/examples/packaging-github-repos)
  * [Packaging Archive Files Example: zlib](https://learn.microsoft.com/en-us/vcpkg/examples/packaging-zipfiles)
  * [Patching example: Patching libpng to work for x64-uwp](https://learn.microsoft.com/en-us/vcpkg/examples/patching)
  * [Add an explicit usage file to a port](https://learn.microsoft.com/en-us/vcpkg/examples/adding-usage)

* [Personalizar una compilación](https://learn.microsoft.com/es-es/visualstudio/msbuild/customize-your-build?view=vs-2022)

* [Personalización de la compilación por carpeta](https://learn.microsoft.com/es-es/visualstudio/msbuild/customize-by-directory?view=vs-2022) 

* [Personalización de una compilación para controlar los archivos generados](https://learn.microsoft.com/es-es/visualstudio/msbuild/customize-builds-for-generated-files?view=vs-2022)

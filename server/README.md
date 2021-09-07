# RestService [![Build Status]
Test task, based on oatpp-starter.

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- src/
|    |
|    |- controller/                      // Folder containing MyController where all endpoints are declared
|    |- dto/                             // DTOs are declared here
|    |- db/                              // Classes for saving data
|    |- AppComponent.hpp                 // Service config
|    |- App.cpp                          // main() is here
|
|- utility/install-oatpp-modules.sh      // utility script to install required oatpp-modules.  
```

---

### Build and Run

#### Using CMake

**Requires** 

- `oatpp` module installed. You may run `utility/install-oatpp-modules.sh` 
script to install required oatpp modules.

```
$ mkdir build && cd build
$ cmake ..
$ make 
$ ./my-project-exe  # - run application.

```

### Work with app
#### Commands:
```
`Create User:`
$curl -X POST "http://localhost:8000/users" -H "accept: application/json" -H "Content-Type: application/json" -d '{"login":"string1","password":"string1"}'
`Get login`
$curl -X GET "http://localhost:8000/users/0"
`Delete user`
$curl -X DELETE "http://localhost:8000/users/0"
`Increment global count`
$curl -X GET "http://localhost:8000/users/inc/0"
`Increment local count`
$curl -X GET "http://localhost:8000/users/inc/personal/0"
```

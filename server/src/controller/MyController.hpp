#ifndef MyController_hpp
#define MyController_hpp

#include <boost/format.hpp>

#include "db/UserArray.hpp"
#include "dto/UserDto.hpp"
#include "dto/ShowLoginDto.hpp"


#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"


#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen
/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
private:
  UserArray users;
  std::atomic<int> counter{0};
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:
  
  /*default method*/
  ENDPOINT("GET", "/", root) {
    auto dto = UserDto::createShared();
    return createDtoResponse(Status::CODE_200, dto);
  }
  
  
  
  /*Create user(
    POST
    http://localhost:8000/users

    RETURN UID
  ) - создать пользователя*/
  
   
  ENDPOINT_INFO(createUser) {
    info->summary = "Create new User";
    info->addConsumes<Object<UserDto>>("application/json");
    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("POST", "users", createUser,
           BODY_DTO(Object<UserDto>, userDto))
  {
    userDto->id = this->users.updateUID();
    userDto->counter = 0;
    this->users.add(userDto);
    return createDtoResponse(Status::CODE_200, userDto);
  }
  
  
  /*WHOAMI - returns login(
      GET
      http://localhost:8000/users/{UID}
  )*/
  ENDPOINT_INFO(getUser) {
    info->summary = "get User";
    info->addConsumes<Object<UserDto>>("application/json");
    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "users/{uID}",getUser, PATH(Int32, uID))
  {
    
    auto showLoginDto = ShowLoginDto::createShared();
    showLoginDto->login = users.getUserDto(int(uID))->login;
    return createDtoResponse(Status::CODE_200, showLoginDto);
  }

  /*Delete 
      DELETE
      http://localhost:8000/users/{UID}
  */
    ENDPOINT_INFO(delUser) {
    info->summary = "delete User";
    info->addConsumes<Object<UserDto>>("application/json");
    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("DELETE", "users/{uID}",delUser, PATH(Int32, uID))
  {
    switch(users.remove(uID)){
    case 200:
      return createResponse(Status::CODE_200, "Deleted ");
    case 204:
      return createResponse(Status::CODE_200, "Not found with that ID ");
    default:
      return createResponse(Status::CODE_500, "Some error"); 
    }
  }

};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */

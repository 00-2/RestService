#ifndef MyController_hpp
#define MyController_hpp


#include "db/UserArray.hpp"
#include "dto/UserDto.hpp"
#include "dto/ShowLoginDto.hpp"
#include "dto/ShowDataDto.hpp"


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
    OATPP_LOGI("Create user", "\n\tlogin:%s\n\tuID:%d", userDto->login->c_str(), int(userDto->id));
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
    if (users.getIndex(uID)!=-1){
      auto showLoginDto = ShowLoginDto::createShared();
      showLoginDto->login = users.getUserDto(int(uID))->login;
      return createDtoResponse(Status::CODE_200, showLoginDto);
    }
    else{
      return createResponse(Status::CODE_204, "Not found with that ID\n");
    }
  }

  /*Delete user 
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
      OATPP_LOGI("Delete user", "\n\tuID:%d", int(uID));
      return createResponse(Status::CODE_200, "Deleted\n");
    case 204:
      //OATPP_LOGI("Delete user", "\n\tTRY TO DELETE, NOT FOUND uID:%d", int(uID));
      return createResponse(Status::CODE_200, "Not found with that ID\n");
    default:
      return createResponse(Status::CODE_500, "Some error\n"); 
    }
  }

   /*local Increment 
      POST
      http://localhost:8000/users/{UID}
  */
  ENDPOINT_INFO(incPersonalCount) {
    info->summary = "incrementPersonalCount";
    info->addConsumes<Object<UserDto>>("application/json");
    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "users/inc/personal/{uID}",incPersonalCount, PATH(Int32, uID))
  {
    if (users.getIndex(uID)!=-1){
      auto personalCounter = users.incPersonalCounter(int(uID));
      auto showDataDto = ShowDataDto::createShared();
      showDataDto->description = ("uID:"+std::to_string(uID)).c_str();
      showDataDto->data = personalCounter;
      OATPP_LOGI("Inc user", "\n\tuID:%d\n\tcounter:%d", int(uID),personalCounter);
      return createDtoResponse(Status::CODE_200,showDataDto);
    }
    else{
      return createResponse(Status::CODE_204, "Not found with that ID\n");
    }
  }

  ENDPOINT_INFO(incGlobalCount) {
    info->summary = "incrementGlobalCount";
    info->addConsumes<Object<UserDto>>("application/json");
    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "users/inc/{uID}",incGlobalCount, PATH(Int32, uID))
  {
    auto showDataDto = ShowDataDto::createShared();
    showDataDto->description = "global";
    showDataDto->data = ++counter;
    OATPP_LOGI("Inc global","\n\tuID:%d\n\tcounter:%d", int(uID), int(counter));
    return createDtoResponse(Status::CODE_200,showDataDto);
  }
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */

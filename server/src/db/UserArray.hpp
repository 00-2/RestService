#include <vector>
#include "../dto/UserDto.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

class UserArray{
    private:
        std::atomic<int> uID{0};
        std::vector<oatpp::web::server::api::ApiController::Object<UserDto>> data;
    public:
        UserArray(){
        }
        void add(oatpp::web::server::api::ApiController::Object<UserDto>user){
            uID++;
            data.push_back(user);
        }
        void remove(int uID){
            int index = uID;
            data.erase(data.begin()+index);
            this->uID = uID;
        }

        oatpp::web::server::api::ApiController::Object<UserDto> getUserDto(int index){
            return data[index];
        }

        void setUID(int tUID){
            uID = tUID;
        }
        int size(){
            return data.size();
        }
        int getUID(){
            return uID;
        }
};
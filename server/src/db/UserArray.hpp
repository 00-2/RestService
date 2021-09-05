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
            if (data[uID]){
                uID = data.size()-1;
                data.push_back(user);
            }
            else{
                int index = uID-1;
                data.insert(data.begin()+index, user);
                uID++;
            }
        }
        void remove(int uID){
            int index = uID-1;
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
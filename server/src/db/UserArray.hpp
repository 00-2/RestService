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
            data.push_back(user);
        }
        int remove(int uID){//return status code
            int index = -1;
            for(int i = 0; i<data.size(); ++i){
                if (uID==data[i]->id){
                    index = i;
                    break;
                }
            }
            if (index!=-1){
                data.erase(data.begin()+index);
                return 200;
            }
            else{
                return 204;
            }
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
        int updateUID(){
            return uID++;
        }
};
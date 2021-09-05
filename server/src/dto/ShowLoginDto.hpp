#ifndef ShowLoginDto_hpp
#define ShowLoginDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)


class ShowLoginDto : public oatpp::DTO {
  DTO_INIT(ShowLoginDto, DTO)
  DTO_FIELD(String, login, "login");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ShowLoginDto_hpp */
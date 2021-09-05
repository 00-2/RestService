#ifndef ShowDataDto_hpp
#define ShowDataDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)


class ShowDataDto : public oatpp::DTO {
  DTO_INIT(ShowDataDto, DTO)
  DTO_FIELD(String, description);
  DTO_FIELD(Int32, data);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ShowDataDto_hpp */

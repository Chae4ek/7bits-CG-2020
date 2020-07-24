#include "Tools/ReaderStruct.h"

bool ReaderStruct::SetStruct(FILE* file_struct, const int x, const int y) {
  if (file_struct) {
    // TODO: check file version
    file = file_struct;

    fread(&info.x_bot, sizeof(int), 1, file);
    fread(&info.y_bot, sizeof(int), 1, file);
    info.x_top = x;
    info.y_top = y;
    info.x_bot += x;
    info.y_bot += y;

    return true;
  }
  return false;
}
struct_info ReaderStruct::GetInfo() const {
  return info;
}
int ReaderStruct::GetNextEntityType() const {
  int type;
  fread(&type, sizeof(int), 1, file);
  return type;
}
#include "Tools/ReaderStruct.h"

ReaderStruct::ReaderStruct(const int x, const int y) {
  info.x_top = x;
  info.y_top = y;
  info.x_bot = x;
  info.y_bot = y;
}

bool ReaderStruct::SetStruct(FILE* file_struct) {
  if (file_struct) {
    // TODO: check file version
    file = file_struct;

    struct_info temp(0, 0, 0, 0);
    fread(&temp.x_bot, sizeof(int), 1, file);
    fread(&temp.y_bot, sizeof(int), 1, file);
    info.x_bot += temp.x_bot;
    info.y_bot += temp.y_bot;

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
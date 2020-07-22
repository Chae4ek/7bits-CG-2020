#include "Tools/ReaderStruct.h"

void ReaderStruct::SetStruct(FILE* file_struct) {
  // TODO: check file version
  file = file_struct;
}
bool ReaderStruct::SetGenerate(const int x, const int y, const int max_x, const int max_y) {
  if (file) {
    fread(&info.x_bot, sizeof(int), 1, file);
    fread(&info.y_bot, sizeof(int), 1, file);
    info.x_top = x;
    info.y_top = y;
    info.x_bot += x;
    info.y_bot += y;
    if (info.x_bot < max_x && info.y_bot < max_y) return true;
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
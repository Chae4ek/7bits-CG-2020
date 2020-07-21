#pragma once

#include <cstdio>

struct struct_info {
 public:
  int x_top;
  int y_top;
  int x_bot;
  int y_bot;

  struct_info(int x_top, int y_top, int x_bot, int y_bot) : x_top(x_top), y_top(y_top), x_bot(x_bot), y_bot(y_bot) {}
};

class IReaderStruct {
 protected:
  FILE* file;
  struct_info info;

 public:
  IReaderStruct() : file(nullptr), info(0, 0, 0, 0) {}

  virtual void SetStruct(FILE* file_struct) = 0;
  virtual bool SetGenerate(const int x, const int y, const int max_x, const int max_y) = 0;
  virtual struct_info GetInfo() const = 0;
  virtual int GetNextEntityType() const = 0;
};

class ReaderStruct : protected IReaderStruct {
 public:
  void SetStruct(FILE* file_struct);
  bool SetGenerate(const int x, const int y, const int max_x, const int max_y);
  struct_info GetInfo() const;
  int GetNextEntityType() const;
};
#pragma once

#include <cstdio>
#include <string>

#include "ECS/Components.h"

struct struct_info {
 public:
  int x_top;
  int y_top;
  int x_bot;
  int y_bot;

  struct_info(const int x_top, const int y_top, const int x_bot, const int y_bot)
      : x_top(x_top), y_top(y_top), x_bot(x_bot), y_bot(y_bot) {}
};

class IReaderStruct {
 protected:
  FILE* file;
  struct_info info;

 public:
  IReaderStruct() : file(nullptr), info(0, 0, 0, 0) {}

  virtual bool SetStruct(FILE* file_struct) = 0;
  virtual struct_info GetInfo() const = 0;

  virtual int GetNext() const = 0;
};

class ReaderStruct : protected IReaderStruct {
 public:
  ReaderStruct(const int x, const int y);

  bool SetStruct(FILE* file_struct);
  struct_info GetInfo() const;

  int GetNext() const;
};
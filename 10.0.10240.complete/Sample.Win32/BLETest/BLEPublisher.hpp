#pragma once
#include <memory>

class BLEPublisher
{
public:
  BLEPublisher();
  ~BLEPublisher();

  bool StartPublish();

private:
  struct IMPL;
  std::unique_ptr<IMPL> m;
};


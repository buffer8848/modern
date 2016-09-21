#include "stdafx.h"
#include "BLEPublisher.hpp"

#include "modern.h"

using namespace Modern;
using namespace Windows::Devices::Bluetooth::Advertisement;
using namespace Windows::Storage::Streams;
using namespace Windows::Foundation;

//-------------------------------------------------------------------------------------------------
typedef struct BLEPublisher::IMPL {
  BluetoothLEAdvertisementPublisher publisher;
  BluetoothLEManufacturerData data;
  DataWriter write;
}IMPL;

//-------------------------------------------------------------------------------------------------
BLEPublisher::BLEPublisher() : m(new IMPL)
{
  Initialize(InitializeType::SingleThreaded);
}


BLEPublisher::~BLEPublisher()
{
}

bool BLEPublisher::StartPublish() {
  m->data.CompanyId(0x1234);
  m->write.WriteInt16(0x1234);
  m->data.Data(m->write.DetachBuffer());
  m->publisher.Advertisement().ManufacturerData().Append(m->data);
  m->publisher.StatusChanged(([](const auto &p, const auto &a) {
    auto status = a.Status();
    auto error = a.Error();
  }));
  m->publisher.Start();

  return true;
}

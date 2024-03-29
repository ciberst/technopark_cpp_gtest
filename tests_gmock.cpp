#include "DArray.h"
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

constexpr char kEmptyStr[] = "";

class Turtle {
 public:
  virtual ~Turtle() = default;
  virtual void PenDown() = 0;
};

class MockTurtle : public Turtle {
 public:
  // MOCK_METHOD0(PenDown, void());
  MOCK_METHOD(void, PenDown, (), (override));
};

class Painter {
 public:
  explicit Painter(Turtle* turtle) : turtle_(turtle) {}

  bool DrawCircle(int x, int y, int r) {
    turtle_->PenDown();
    return true;
  }

  Turtle* turtle_;
};

TEST(PainterTest, CanDrawSomething) {
  MockTurtle turtle;
  EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));

  Painter painter(&turtle);
  EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}

//class MockDArray : public DArray {
// public:
//  explicit MockDArray(size_t buffer_size) : DArray(buffer_size){};
//  MOCK_METHOD0(Reallocate, void());
//};

class MockDArray : public DArray {
 public:
  explicit MockDArray(size_t buffer_size) : DArray(buffer_size){};
  MOCK_METHOD0(DoReallocate, void());
  // void DoReallocate() {}

 private:
  void Reallocate() override {
    DArray::Reallocate();
    DoReallocate();
  }
};

TEST(DynamicArrayTest, ReallocateCalledOnce) {
  const int kCount = 2;
  MockDArray mockdarray{kCount};
  //EXPECT_CALL(mockdarray, Reallocate()).Times(AtLeast(1));
  EXPECT_CALL(mockdarray, DoReallocate()).Times(AtLeast(1));
  ASSERT_EQ(mockdarray.Capacity(), kCount);
  mockdarray.PushBack(5);
  mockdarray.PushBack(5);
  mockdarray.PushBack(5);
  ASSERT_EQ(mockdarray.Capacity(), kCount * 2);
  mockdarray.PushBack(5);
  mockdarray.PushBack(5);
}

class Packet;

class ConcretePacketStream {
 public:
  void AppendPacket(Packet* new_packet){};
  const Packet* GetPacket(size_t packet_number) const { return nullptr; };
  size_t NumberOfPackets() const { return 0; };
};

class MockPacketStream {
 public:
  // MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
  // MOCK_METHOD(size_t, NumberOfPackets, (), (const));

  MOCK_CONST_METHOD1(GetPacket, const Packet*(size_t packet_number));
  MOCK_CONST_METHOD0(NumberOfPackets, size_t());
};

template <class PacketStream>
class PacketReader {
 public:
  explicit PacketReader(PacketStream* stream) : stream_(stream){};

  void ReadPackets(size_t packet_num) { stream_->GetPacket(packet_num); };

 private:
  PacketStream* stream_;
};

TEST(TestNonVirtual, HelloWorld) {
  size_t packet_num = 1;
  MockPacketStream mock_stream;
  EXPECT_CALL(mock_stream, GetPacket(packet_num)).Times(AtLeast(1));
  PacketReader<MockPacketStream> reader(&mock_stream);
  reader.ReadPackets(1);
}

class FileInterface {
 public:
  virtual bool Open(const char* path, int& mode) = 0;
};

class File : public FileInterface {
 public:
  virtual bool Open(const char* path, int& mode) {
    return OpenFile(path, mode);
  }

  static bool OpenFile(const char* path, int& mode) { return false; }
};

class MockFI : public FileInterface {
 public:
  MOCK_METHOD2(Open, bool(const char* path, int& mode));
};

class ClientFileInterface {
 public:
  explicit ClientFileInterface(FileInterface* fi) : fi_(fi) {}

  bool DoRead() {
    int mode = 0;
    const bool result = fi_->Open(kEmptyStr, mode);
    std::cout << "mode: "  << mode << std::endl;
    return result;
  }

  FileInterface* fi_ = nullptr;
};

TEST(TestStatic, HelloWorld) {
  MockFI fi;
  int _ = 0;
  EXPECT_CALL(fi, Open(kEmptyStr, _))
      .WillOnce(DoAll(SetArgReferee<1>(0), Return(true)));

  ClientFileInterface c{&fi};
  if (c.DoRead()) {
    std::cout << " Return value is true" << std::endl;
  }
}

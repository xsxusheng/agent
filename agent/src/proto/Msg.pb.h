// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Msg.proto

#ifndef PROTOBUF_Msg_2eproto__INCLUDED
#define PROTOBUF_Msg_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace com {
namespace fiberhome {
namespace fums {
namespace proto {
class Header;
class HeaderDefaultTypeInternal;
extern HeaderDefaultTypeInternal _Header_default_instance_;
class Major;
class MajorDefaultTypeInternal;
extern MajorDefaultTypeInternal _Major_default_instance_;
}  // namespace proto
}  // namespace fums
}  // namespace fiberhome
}  // namespace com

namespace com {
namespace fiberhome {
namespace fums {
namespace proto {

namespace protobuf_Msg_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static void InitDefaultsImpl();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_Msg_2eproto

enum Header_DIRECTION {
  Header_DIRECTION_AGENTOFUMS = 0,
  Header_DIRECTION_FUMSTOAGEN = 1,
  Header_DIRECTION_OTHER = 2,
  Header_DIRECTION_Header_DIRECTION_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Header_DIRECTION_Header_DIRECTION_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Header_DIRECTION_IsValid(int value);
const Header_DIRECTION Header_DIRECTION_DIRECTION_MIN = Header_DIRECTION_AGENTOFUMS;
const Header_DIRECTION Header_DIRECTION_DIRECTION_MAX = Header_DIRECTION_OTHER;
const int Header_DIRECTION_DIRECTION_ARRAYSIZE = Header_DIRECTION_DIRECTION_MAX + 1;

const ::google::protobuf::EnumDescriptor* Header_DIRECTION_descriptor();
inline const ::std::string& Header_DIRECTION_Name(Header_DIRECTION value) {
  return ::google::protobuf::internal::NameOfEnum(
    Header_DIRECTION_descriptor(), value);
}
inline bool Header_DIRECTION_Parse(
    const ::std::string& name, Header_DIRECTION* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Header_DIRECTION>(
    Header_DIRECTION_descriptor(), name, value);
}
enum Header_DataType {
  Header_DataType_PERF = 0,
  Header_DataType_EVENT = 1,
  Header_DataType_APP = 2,
  Header_DataType_ACS_EVENT = 3,
  Header_DataType_STB_INSPECT = 4,
  Header_DataType_RESPONSE = 5,
  Header_DataType_UPHOSTCFG = 6,
  Header_DataType_ALARM = 100,
  Header_DataType_CONFIG = 200,
  Header_DataType_CTRL_APP = 201,
  Header_DataType_SOFTWARE = 202,
  Header_DataType_REALQUERYHOSTCFG = 203,
  Header_DataType_HASWITCH = 204,
  Header_DataType_HEART = 300,
  Header_DataType_Header_DataType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Header_DataType_Header_DataType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Header_DataType_IsValid(int value);
const Header_DataType Header_DataType_DataType_MIN = Header_DataType_PERF;
const Header_DataType Header_DataType_DataType_MAX = Header_DataType_HEART;
const int Header_DataType_DataType_ARRAYSIZE = Header_DataType_DataType_MAX + 1;

const ::google::protobuf::EnumDescriptor* Header_DataType_descriptor();
inline const ::std::string& Header_DataType_Name(Header_DataType value) {
  return ::google::protobuf::internal::NameOfEnum(
    Header_DataType_descriptor(), value);
}
inline bool Header_DataType_Parse(
    const ::std::string& name, Header_DataType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Header_DataType>(
    Header_DataType_descriptor(), name, value);
}
// ===================================================================

class Major : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:com.fiberhome.fums.proto.Major) */ {
 public:
  Major();
  virtual ~Major();

  Major(const Major& from);

  inline Major& operator=(const Major& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Major(Major&& from) noexcept
    : Major() {
    *this = ::std::move(from);
  }

  inline Major& operator=(Major&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Major& default_instance();

  static inline const Major* internal_default_instance() {
    return reinterpret_cast<const Major*>(
               &_Major_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Major* other);
  friend void swap(Major& a, Major& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Major* New() const PROTOBUF_FINAL { return New(NULL); }

  Major* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Major& from);
  void MergeFrom(const Major& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Major* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string body = 2;
  void clear_body();
  static const int kBodyFieldNumber = 2;
  const ::std::string& body() const;
  void set_body(const ::std::string& value);
  #if LANG_CXX11
  void set_body(::std::string&& value);
  #endif
  void set_body(const char* value);
  void set_body(const char* value, size_t size);
  ::std::string* mutable_body();
  ::std::string* release_body();
  void set_allocated_body(::std::string* body);

  // .com.fiberhome.fums.proto.Header header = 1;
  bool has_header() const;
  void clear_header();
  static const int kHeaderFieldNumber = 1;
  const ::com::fiberhome::fums::proto::Header& header() const;
  ::com::fiberhome::fums::proto::Header* mutable_header();
  ::com::fiberhome::fums::proto::Header* release_header();
  void set_allocated_header(::com::fiberhome::fums::proto::Header* header);

  // @@protoc_insertion_point(class_scope:com.fiberhome.fums.proto.Major)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr body_;
  ::com::fiberhome::fums::proto::Header* header_;
  mutable int _cached_size_;
  friend struct protobuf_Msg_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Header : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:com.fiberhome.fums.proto.Header) */ {
 public:
  Header();
  virtual ~Header();

  Header(const Header& from);

  inline Header& operator=(const Header& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Header(Header&& from) noexcept
    : Header() {
    *this = ::std::move(from);
  }

  inline Header& operator=(Header&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Header& default_instance();

  static inline const Header* internal_default_instance() {
    return reinterpret_cast<const Header*>(
               &_Header_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(Header* other);
  friend void swap(Header& a, Header& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Header* New() const PROTOBUF_FINAL { return New(NULL); }

  Header* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Header& from);
  void MergeFrom(const Header& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Header* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef Header_DIRECTION DIRECTION;
  static const DIRECTION AGENTOFUMS =
    Header_DIRECTION_AGENTOFUMS;
  static const DIRECTION FUMSTOAGEN =
    Header_DIRECTION_FUMSTOAGEN;
  static const DIRECTION OTHER =
    Header_DIRECTION_OTHER;
  static inline bool DIRECTION_IsValid(int value) {
    return Header_DIRECTION_IsValid(value);
  }
  static const DIRECTION DIRECTION_MIN =
    Header_DIRECTION_DIRECTION_MIN;
  static const DIRECTION DIRECTION_MAX =
    Header_DIRECTION_DIRECTION_MAX;
  static const int DIRECTION_ARRAYSIZE =
    Header_DIRECTION_DIRECTION_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  DIRECTION_descriptor() {
    return Header_DIRECTION_descriptor();
  }
  static inline const ::std::string& DIRECTION_Name(DIRECTION value) {
    return Header_DIRECTION_Name(value);
  }
  static inline bool DIRECTION_Parse(const ::std::string& name,
      DIRECTION* value) {
    return Header_DIRECTION_Parse(name, value);
  }

  typedef Header_DataType DataType;
  static const DataType PERF =
    Header_DataType_PERF;
  static const DataType EVENT =
    Header_DataType_EVENT;
  static const DataType APP =
    Header_DataType_APP;
  static const DataType ACS_EVENT =
    Header_DataType_ACS_EVENT;
  static const DataType STB_INSPECT =
    Header_DataType_STB_INSPECT;
  static const DataType RESPONSE =
    Header_DataType_RESPONSE;
  static const DataType UPHOSTCFG =
    Header_DataType_UPHOSTCFG;
  static const DataType ALARM =
    Header_DataType_ALARM;
  static const DataType CONFIG =
    Header_DataType_CONFIG;
  static const DataType CTRL_APP =
    Header_DataType_CTRL_APP;
  static const DataType SOFTWARE =
    Header_DataType_SOFTWARE;
  static const DataType REALQUERYHOSTCFG =
    Header_DataType_REALQUERYHOSTCFG;
  static const DataType HASWITCH =
    Header_DataType_HASWITCH;
  static const DataType HEART =
    Header_DataType_HEART;
  static inline bool DataType_IsValid(int value) {
    return Header_DataType_IsValid(value);
  }
  static const DataType DataType_MIN =
    Header_DataType_DataType_MIN;
  static const DataType DataType_MAX =
    Header_DataType_DataType_MAX;
  static const int DataType_ARRAYSIZE =
    Header_DataType_DataType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  DataType_descriptor() {
    return Header_DataType_descriptor();
  }
  static inline const ::std::string& DataType_Name(DataType value) {
    return Header_DataType_Name(value);
  }
  static inline bool DataType_Parse(const ::std::string& name,
      DataType* value) {
    return Header_DataType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // string host = 1;
  void clear_host();
  static const int kHostFieldNumber = 1;
  const ::std::string& host() const;
  void set_host(const ::std::string& value);
  #if LANG_CXX11
  void set_host(::std::string&& value);
  #endif
  void set_host(const char* value);
  void set_host(const char* value, size_t size);
  ::std::string* mutable_host();
  ::std::string* release_host();
  void set_allocated_host(::std::string* host);

  // string ip = 2;
  void clear_ip();
  static const int kIpFieldNumber = 2;
  const ::std::string& ip() const;
  void set_ip(const ::std::string& value);
  #if LANG_CXX11
  void set_ip(::std::string&& value);
  #endif
  void set_ip(const char* value);
  void set_ip(const char* value, size_t size);
  ::std::string* mutable_ip();
  ::std::string* release_ip();
  void set_allocated_ip(::std::string* ip);

  // string rabbitmqInfo = 7;
  void clear_rabbitmqinfo();
  static const int kRabbitmqInfoFieldNumber = 7;
  const ::std::string& rabbitmqinfo() const;
  void set_rabbitmqinfo(const ::std::string& value);
  #if LANG_CXX11
  void set_rabbitmqinfo(::std::string&& value);
  #endif
  void set_rabbitmqinfo(const char* value);
  void set_rabbitmqinfo(const char* value, size_t size);
  ::std::string* mutable_rabbitmqinfo();
  ::std::string* release_rabbitmqinfo();
  void set_allocated_rabbitmqinfo(::std::string* rabbitmqinfo);

  // int64 timestamp = 4;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 4;
  ::google::protobuf::int64 timestamp() const;
  void set_timestamp(::google::protobuf::int64 value);

  // int32 seq = 3;
  void clear_seq();
  static const int kSeqFieldNumber = 3;
  ::google::protobuf::int32 seq() const;
  void set_seq(::google::protobuf::int32 value);

  // .com.fiberhome.fums.proto.Header.DIRECTION direction = 5;
  void clear_direction();
  static const int kDirectionFieldNumber = 5;
  ::com::fiberhome::fums::proto::Header_DIRECTION direction() const;
  void set_direction(::com::fiberhome::fums::proto::Header_DIRECTION value);

  // .com.fiberhome.fums.proto.Header.DataType type = 6;
  void clear_type();
  static const int kTypeFieldNumber = 6;
  ::com::fiberhome::fums::proto::Header_DataType type() const;
  void set_type(::com::fiberhome::fums::proto::Header_DataType value);

  // @@protoc_insertion_point(class_scope:com.fiberhome.fums.proto.Header)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr host_;
  ::google::protobuf::internal::ArenaStringPtr ip_;
  ::google::protobuf::internal::ArenaStringPtr rabbitmqinfo_;
  ::google::protobuf::int64 timestamp_;
  ::google::protobuf::int32 seq_;
  int direction_;
  int type_;
  mutable int _cached_size_;
  friend struct protobuf_Msg_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Major

// .com.fiberhome.fums.proto.Header header = 1;
inline bool Major::has_header() const {
  return this != internal_default_instance() && header_ != NULL;
}
inline void Major::clear_header() {
  if (GetArenaNoVirtual() == NULL && header_ != NULL) delete header_;
  header_ = NULL;
}
inline const ::com::fiberhome::fums::proto::Header& Major::header() const {
  const ::com::fiberhome::fums::proto::Header* p = header_;
  // @@protoc_insertion_point(field_get:com.fiberhome.fums.proto.Major.header)
  return p != NULL ? *p : *reinterpret_cast<const ::com::fiberhome::fums::proto::Header*>(
      &::com::fiberhome::fums::proto::_Header_default_instance_);
}
inline ::com::fiberhome::fums::proto::Header* Major::mutable_header() {
  
  if (header_ == NULL) {
    header_ = new ::com::fiberhome::fums::proto::Header;
  }
  // @@protoc_insertion_point(field_mutable:com.fiberhome.fums.proto.Major.header)
  return header_;
}
inline ::com::fiberhome::fums::proto::Header* Major::release_header() {
  // @@protoc_insertion_point(field_release:com.fiberhome.fums.proto.Major.header)
  
  ::com::fiberhome::fums::proto::Header* temp = header_;
  header_ = NULL;
  return temp;
}
inline void Major::set_allocated_header(::com::fiberhome::fums::proto::Header* header) {
  delete header_;
  header_ = header;
  if (header) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:com.fiberhome.fums.proto.Major.header)
}

// string body = 2;
inline void Major::clear_body() {
  body_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Major::body() const {
  // @@protoc_insertion_point(field_get:com.fiberhome.fums.proto.Major.body)
  return body_.GetNoArena();
}
inline void Major::set_body(const ::std::string& value) {
  
  body_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:com.fiberhome.fums.proto.Major.body)
}
#if LANG_CXX11
inline void Major::set_body(::std::string&& value) {
  
  body_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:com.fiberhome.fums.proto.Major.body)
}
#endif
inline void Major::set_body(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  body_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:com.fiberhome.fums.proto.Major.body)
}
inline void Major::set_body(const char* value, size_t size) {
  
  body_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:com.fiberhome.fums.proto.Major.body)
}
inline ::std::string* Major::mutable_body() {
  
  // @@protoc_insertion_point(field_mutable:com.fiberhome.fums.proto.Major.body)
  return body_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Major::release_body() {
  // @@protoc_insertion_point(field_release:com.fiberhome.fums.proto.Major.body)
  
  return body_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Major::set_allocated_body(::std::string* body) {
  if (body != NULL) {
    
  } else {
    
  }
  body_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), body);
  // @@protoc_insertion_point(field_set_allocated:com.fiberhome.fums.proto.Major.body)
}

// -------------------------------------------------------------------

// Header

// string host = 1;
inline void Header::clear_host() {
  host_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Header::host() const {
  // @@protoc_insertion_point(field_get:com.fiberhome.fums.proto.Header.host)
  return host_.GetNoArena();
}
inline void Header::set_host(const ::std::string& value) {
  
  host_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:com.fiberhome.fums.proto.Header.host)
}
#if LANG_CXX11
inline void Header::set_host(::std::string&& value) {
  
  host_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:com.fiberhome.fums.proto.Header.host)
}
#endif
inline void Header::set_host(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  host_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:com.fiberhome.fums.proto.Header.host)
}
inline void Header::set_host(const char* value, size_t size) {
  
  host_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:com.fiberhome.fums.proto.Header.host)
}
inline ::std::string* Header::mutable_host() {
  
  // @@protoc_insertion_point(field_mutable:com.fiberhome.fums.proto.Header.host)
  return host_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Header::release_host() {
  // @@protoc_insertion_point(field_release:com.fiberhome.fums.proto.Header.host)
  
  return host_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Header::set_allocated_host(::std::string* host) {
  if (host != NULL) {
    
  } else {
    
  }
  host_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), host);
  // @@protoc_insertion_point(field_set_allocated:com.fiberhome.fums.proto.Header.host)
}

// string ip = 2;
inline void Header::clear_ip() {
  ip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Header::ip() const {
  // @@protoc_insertion_point(field_get:com.fiberhome.fums.proto.Header.ip)
  return ip_.GetNoArena();
}
inline void Header::set_ip(const ::std::string& value) {
  
  ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:com.fiberhome.fums.proto.Header.ip)
}
#if LANG_CXX11
inline void Header::set_ip(::std::string&& value) {
  
  ip_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:com.fiberhome.fums.proto.Header.ip)
}
#endif
inline void Header::set_ip(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:com.fiberhome.fums.proto.Header.ip)
}
inline void Header::set_ip(const char* value, size_t size) {
  
  ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:com.fiberhome.fums.proto.Header.ip)
}
inline ::std::string* Header::mutable_ip() {
  
  // @@protoc_insertion_point(field_mutable:com.fiberhome.fums.proto.Header.ip)
  return ip_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Header::release_ip() {
  // @@protoc_insertion_point(field_release:com.fiberhome.fums.proto.Header.ip)
  
  return ip_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Header::set_allocated_ip(::std::string* ip) {
  if (ip != NULL) {
    
  } else {
    
  }
  ip_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ip);
  // @@protoc_insertion_point(field_set_allocated:com.fiberhome.fums.proto.Header.ip)
}

// int32 seq = 3;
inline void Header::clear_seq() {
  seq_ = 0;
}
inline ::google::protobuf::int32 Header::seq() const {
  // @@protoc_insertion_point(field_get:com.fiberhome.fums.proto.Header.seq)
  return seq_;
}
inline void Header::set_seq(::google::protobuf::int32 value) {
  
  seq_ = value;
  // @@protoc_insertion_point(field_set:com.fiberhome.fums.proto.Header.seq)
}

// int64 timestamp = 4;
inline void Header::clear_timestamp() {
  timestamp_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 Header::timestamp() const {
  // @@protoc_insertion_point(field_get:com.fiberhome.fums.proto.Header.timestamp)
  return timestamp_;
}
inline void Header::set_timestamp(::google::protobuf::int64 value) {
  
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:com.fiberhome.fums.proto.Header.timestamp)
}

// .com.fiberhome.fums.proto.Header.DIRECTION direction = 5;
inline void Header::clear_direction() {
  direction_ = 0;
}
inline ::com::fiberhome::fums::proto::Header_DIRECTION Header::direction() const {
  // @@protoc_insertion_point(field_get:com.fiberhome.fums.proto.Header.direction)
  return static_cast< ::com::fiberhome::fums::proto::Header_DIRECTION >(direction_);
}
inline void Header::set_direction(::com::fiberhome::fums::proto::Header_DIRECTION value) {
  
  direction_ = value;
  // @@protoc_insertion_point(field_set:com.fiberhome.fums.proto.Header.direction)
}

// .com.fiberhome.fums.proto.Header.DataType type = 6;
inline void Header::clear_type() {
  type_ = 0;
}
inline ::com::fiberhome::fums::proto::Header_DataType Header::type() const {
  // @@protoc_insertion_point(field_get:com.fiberhome.fums.proto.Header.type)
  return static_cast< ::com::fiberhome::fums::proto::Header_DataType >(type_);
}
inline void Header::set_type(::com::fiberhome::fums::proto::Header_DataType value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:com.fiberhome.fums.proto.Header.type)
}

// string rabbitmqInfo = 7;
inline void Header::clear_rabbitmqinfo() {
  rabbitmqinfo_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Header::rabbitmqinfo() const {
  // @@protoc_insertion_point(field_get:com.fiberhome.fums.proto.Header.rabbitmqInfo)
  return rabbitmqinfo_.GetNoArena();
}
inline void Header::set_rabbitmqinfo(const ::std::string& value) {
  
  rabbitmqinfo_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:com.fiberhome.fums.proto.Header.rabbitmqInfo)
}
#if LANG_CXX11
inline void Header::set_rabbitmqinfo(::std::string&& value) {
  
  rabbitmqinfo_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:com.fiberhome.fums.proto.Header.rabbitmqInfo)
}
#endif
inline void Header::set_rabbitmqinfo(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  rabbitmqinfo_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:com.fiberhome.fums.proto.Header.rabbitmqInfo)
}
inline void Header::set_rabbitmqinfo(const char* value, size_t size) {
  
  rabbitmqinfo_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:com.fiberhome.fums.proto.Header.rabbitmqInfo)
}
inline ::std::string* Header::mutable_rabbitmqinfo() {
  
  // @@protoc_insertion_point(field_mutable:com.fiberhome.fums.proto.Header.rabbitmqInfo)
  return rabbitmqinfo_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Header::release_rabbitmqinfo() {
  // @@protoc_insertion_point(field_release:com.fiberhome.fums.proto.Header.rabbitmqInfo)
  
  return rabbitmqinfo_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Header::set_allocated_rabbitmqinfo(::std::string* rabbitmqinfo) {
  if (rabbitmqinfo != NULL) {
    
  } else {
    
  }
  rabbitmqinfo_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), rabbitmqinfo);
  // @@protoc_insertion_point(field_set_allocated:com.fiberhome.fums.proto.Header.rabbitmqInfo)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace proto
}  // namespace fums
}  // namespace fiberhome
}  // namespace com

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::com::fiberhome::fums::proto::Header_DIRECTION> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::com::fiberhome::fums::proto::Header_DIRECTION>() {
  return ::com::fiberhome::fums::proto::Header_DIRECTION_descriptor();
}
template <> struct is_proto_enum< ::com::fiberhome::fums::proto::Header_DataType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::com::fiberhome::fums::proto::Header_DataType>() {
  return ::com::fiberhome::fums::proto::Header_DataType_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Msg_2eproto__INCLUDED

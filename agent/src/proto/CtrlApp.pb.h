// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CtrlApp.proto

#ifndef PROTOBUF_CtrlApp_2eproto__INCLUDED
#define PROTOBUF_CtrlApp_2eproto__INCLUDED

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
#include "CommonDefine.pb.h"
// @@protoc_insertion_point(includes)
namespace proto {
class CtrlAppData;
class CtrlAppDataDefaultTypeInternal;
extern CtrlAppDataDefaultTypeInternal _CtrlAppData_default_instance_;
class CtrlAppRstResponse;
class CtrlAppRstResponseDefaultTypeInternal;
extern CtrlAppRstResponseDefaultTypeInternal _CtrlAppRstResponse_default_instance_;
}  // namespace proto

namespace proto {

namespace protobuf_CtrlApp_2eproto {
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
}  // namespace protobuf_CtrlApp_2eproto

enum CtrlAppData_CtrlTypeEnum {
  CtrlAppData_CtrlTypeEnum_START = 0,
  CtrlAppData_CtrlTypeEnum_STOP = 1,
  CtrlAppData_CtrlTypeEnum_RESTART = 2,
  CtrlAppData_CtrlTypeEnum_HASTART = 3,
  CtrlAppData_CtrlTypeEnum_HARESTART = 4,
  CtrlAppData_CtrlTypeEnum_CtrlAppData_CtrlTypeEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  CtrlAppData_CtrlTypeEnum_CtrlAppData_CtrlTypeEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool CtrlAppData_CtrlTypeEnum_IsValid(int value);
const CtrlAppData_CtrlTypeEnum CtrlAppData_CtrlTypeEnum_CtrlTypeEnum_MIN = CtrlAppData_CtrlTypeEnum_START;
const CtrlAppData_CtrlTypeEnum CtrlAppData_CtrlTypeEnum_CtrlTypeEnum_MAX = CtrlAppData_CtrlTypeEnum_HARESTART;
const int CtrlAppData_CtrlTypeEnum_CtrlTypeEnum_ARRAYSIZE = CtrlAppData_CtrlTypeEnum_CtrlTypeEnum_MAX + 1;

const ::google::protobuf::EnumDescriptor* CtrlAppData_CtrlTypeEnum_descriptor();
inline const ::std::string& CtrlAppData_CtrlTypeEnum_Name(CtrlAppData_CtrlTypeEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    CtrlAppData_CtrlTypeEnum_descriptor(), value);
}
inline bool CtrlAppData_CtrlTypeEnum_Parse(
    const ::std::string& name, CtrlAppData_CtrlTypeEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<CtrlAppData_CtrlTypeEnum>(
    CtrlAppData_CtrlTypeEnum_descriptor(), name, value);
}
// ===================================================================

class CtrlAppData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto.CtrlAppData) */ {
 public:
  CtrlAppData();
  virtual ~CtrlAppData();

  CtrlAppData(const CtrlAppData& from);

  inline CtrlAppData& operator=(const CtrlAppData& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CtrlAppData(CtrlAppData&& from) noexcept
    : CtrlAppData() {
    *this = ::std::move(from);
  }

  inline CtrlAppData& operator=(CtrlAppData&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const CtrlAppData& default_instance();

  static inline const CtrlAppData* internal_default_instance() {
    return reinterpret_cast<const CtrlAppData*>(
               &_CtrlAppData_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(CtrlAppData* other);
  friend void swap(CtrlAppData& a, CtrlAppData& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CtrlAppData* New() const PROTOBUF_FINAL { return New(NULL); }

  CtrlAppData* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CtrlAppData& from);
  void MergeFrom(const CtrlAppData& from);
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
  void InternalSwap(CtrlAppData* other);
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

  typedef CtrlAppData_CtrlTypeEnum CtrlTypeEnum;
  static const CtrlTypeEnum START =
    CtrlAppData_CtrlTypeEnum_START;
  static const CtrlTypeEnum STOP =
    CtrlAppData_CtrlTypeEnum_STOP;
  static const CtrlTypeEnum RESTART =
    CtrlAppData_CtrlTypeEnum_RESTART;
  static const CtrlTypeEnum HASTART =
    CtrlAppData_CtrlTypeEnum_HASTART;
  static const CtrlTypeEnum HARESTART =
    CtrlAppData_CtrlTypeEnum_HARESTART;
  static inline bool CtrlTypeEnum_IsValid(int value) {
    return CtrlAppData_CtrlTypeEnum_IsValid(value);
  }
  static const CtrlTypeEnum CtrlTypeEnum_MIN =
    CtrlAppData_CtrlTypeEnum_CtrlTypeEnum_MIN;
  static const CtrlTypeEnum CtrlTypeEnum_MAX =
    CtrlAppData_CtrlTypeEnum_CtrlTypeEnum_MAX;
  static const int CtrlTypeEnum_ARRAYSIZE =
    CtrlAppData_CtrlTypeEnum_CtrlTypeEnum_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CtrlTypeEnum_descriptor() {
    return CtrlAppData_CtrlTypeEnum_descriptor();
  }
  static inline const ::std::string& CtrlTypeEnum_Name(CtrlTypeEnum value) {
    return CtrlAppData_CtrlTypeEnum_Name(value);
  }
  static inline bool CtrlTypeEnum_Parse(const ::std::string& name,
      CtrlTypeEnum* value) {
    return CtrlAppData_CtrlTypeEnum_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // string appType = 2;
  void clear_apptype();
  static const int kAppTypeFieldNumber = 2;
  const ::std::string& apptype() const;
  void set_apptype(const ::std::string& value);
  #if LANG_CXX11
  void set_apptype(::std::string&& value);
  #endif
  void set_apptype(const char* value);
  void set_apptype(const char* value, size_t size);
  ::std::string* mutable_apptype();
  ::std::string* release_apptype();
  void set_allocated_apptype(::std::string* apptype);

  // int64 uniqueId = 1;
  void clear_uniqueid();
  static const int kUniqueIdFieldNumber = 1;
  ::google::protobuf::int64 uniqueid() const;
  void set_uniqueid(::google::protobuf::int64 value);

  // .proto.EnumDefineData.AppTypeEnum appTypeCode = 3;
  void clear_apptypecode();
  static const int kAppTypeCodeFieldNumber = 3;
  ::proto::EnumDefineData_AppTypeEnum apptypecode() const;
  void set_apptypecode(::proto::EnumDefineData_AppTypeEnum value);

  // .proto.CtrlAppData.CtrlTypeEnum ctrlType = 4;
  void clear_ctrltype();
  static const int kCtrlTypeFieldNumber = 4;
  ::proto::CtrlAppData_CtrlTypeEnum ctrltype() const;
  void set_ctrltype(::proto::CtrlAppData_CtrlTypeEnum value);

  // @@protoc_insertion_point(class_scope:proto.CtrlAppData)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr apptype_;
  ::google::protobuf::int64 uniqueid_;
  int apptypecode_;
  int ctrltype_;
  mutable int _cached_size_;
  friend struct protobuf_CtrlApp_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class CtrlAppRstResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto.CtrlAppRstResponse) */ {
 public:
  CtrlAppRstResponse();
  virtual ~CtrlAppRstResponse();

  CtrlAppRstResponse(const CtrlAppRstResponse& from);

  inline CtrlAppRstResponse& operator=(const CtrlAppRstResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CtrlAppRstResponse(CtrlAppRstResponse&& from) noexcept
    : CtrlAppRstResponse() {
    *this = ::std::move(from);
  }

  inline CtrlAppRstResponse& operator=(CtrlAppRstResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const CtrlAppRstResponse& default_instance();

  static inline const CtrlAppRstResponse* internal_default_instance() {
    return reinterpret_cast<const CtrlAppRstResponse*>(
               &_CtrlAppRstResponse_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(CtrlAppRstResponse* other);
  friend void swap(CtrlAppRstResponse& a, CtrlAppRstResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CtrlAppRstResponse* New() const PROTOBUF_FINAL { return New(NULL); }

  CtrlAppRstResponse* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CtrlAppRstResponse& from);
  void MergeFrom(const CtrlAppRstResponse& from);
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
  void InternalSwap(CtrlAppRstResponse* other);
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

  // .proto.CommonResponse res = 2;
  bool has_res() const;
  void clear_res();
  static const int kResFieldNumber = 2;
  const ::proto::CommonResponse& res() const;
  ::proto::CommonResponse* mutable_res();
  ::proto::CommonResponse* release_res();
  void set_allocated_res(::proto::CommonResponse* res);

  // int64 uniqueId = 1;
  void clear_uniqueid();
  static const int kUniqueIdFieldNumber = 1;
  ::google::protobuf::int64 uniqueid() const;
  void set_uniqueid(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:proto.CtrlAppRstResponse)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::proto::CommonResponse* res_;
  ::google::protobuf::int64 uniqueid_;
  mutable int _cached_size_;
  friend struct protobuf_CtrlApp_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CtrlAppData

// int64 uniqueId = 1;
inline void CtrlAppData::clear_uniqueid() {
  uniqueid_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 CtrlAppData::uniqueid() const {
  // @@protoc_insertion_point(field_get:proto.CtrlAppData.uniqueId)
  return uniqueid_;
}
inline void CtrlAppData::set_uniqueid(::google::protobuf::int64 value) {
  
  uniqueid_ = value;
  // @@protoc_insertion_point(field_set:proto.CtrlAppData.uniqueId)
}

// string appType = 2;
inline void CtrlAppData::clear_apptype() {
  apptype_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CtrlAppData::apptype() const {
  // @@protoc_insertion_point(field_get:proto.CtrlAppData.appType)
  return apptype_.GetNoArena();
}
inline void CtrlAppData::set_apptype(const ::std::string& value) {
  
  apptype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:proto.CtrlAppData.appType)
}
#if LANG_CXX11
inline void CtrlAppData::set_apptype(::std::string&& value) {
  
  apptype_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:proto.CtrlAppData.appType)
}
#endif
inline void CtrlAppData::set_apptype(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  apptype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:proto.CtrlAppData.appType)
}
inline void CtrlAppData::set_apptype(const char* value, size_t size) {
  
  apptype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:proto.CtrlAppData.appType)
}
inline ::std::string* CtrlAppData::mutable_apptype() {
  
  // @@protoc_insertion_point(field_mutable:proto.CtrlAppData.appType)
  return apptype_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CtrlAppData::release_apptype() {
  // @@protoc_insertion_point(field_release:proto.CtrlAppData.appType)
  
  return apptype_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CtrlAppData::set_allocated_apptype(::std::string* apptype) {
  if (apptype != NULL) {
    
  } else {
    
  }
  apptype_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), apptype);
  // @@protoc_insertion_point(field_set_allocated:proto.CtrlAppData.appType)
}

// .proto.EnumDefineData.AppTypeEnum appTypeCode = 3;
inline void CtrlAppData::clear_apptypecode() {
  apptypecode_ = 0;
}
inline ::proto::EnumDefineData_AppTypeEnum CtrlAppData::apptypecode() const {
  // @@protoc_insertion_point(field_get:proto.CtrlAppData.appTypeCode)
  return static_cast< ::proto::EnumDefineData_AppTypeEnum >(apptypecode_);
}
inline void CtrlAppData::set_apptypecode(::proto::EnumDefineData_AppTypeEnum value) {
  
  apptypecode_ = value;
  // @@protoc_insertion_point(field_set:proto.CtrlAppData.appTypeCode)
}

// .proto.CtrlAppData.CtrlTypeEnum ctrlType = 4;
inline void CtrlAppData::clear_ctrltype() {
  ctrltype_ = 0;
}
inline ::proto::CtrlAppData_CtrlTypeEnum CtrlAppData::ctrltype() const {
  // @@protoc_insertion_point(field_get:proto.CtrlAppData.ctrlType)
  return static_cast< ::proto::CtrlAppData_CtrlTypeEnum >(ctrltype_);
}
inline void CtrlAppData::set_ctrltype(::proto::CtrlAppData_CtrlTypeEnum value) {
  
  ctrltype_ = value;
  // @@protoc_insertion_point(field_set:proto.CtrlAppData.ctrlType)
}

// -------------------------------------------------------------------

// CtrlAppRstResponse

// int64 uniqueId = 1;
inline void CtrlAppRstResponse::clear_uniqueid() {
  uniqueid_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 CtrlAppRstResponse::uniqueid() const {
  // @@protoc_insertion_point(field_get:proto.CtrlAppRstResponse.uniqueId)
  return uniqueid_;
}
inline void CtrlAppRstResponse::set_uniqueid(::google::protobuf::int64 value) {
  
  uniqueid_ = value;
  // @@protoc_insertion_point(field_set:proto.CtrlAppRstResponse.uniqueId)
}

// .proto.CommonResponse res = 2;
inline bool CtrlAppRstResponse::has_res() const {
  return this != internal_default_instance() && res_ != NULL;
}
inline void CtrlAppRstResponse::clear_res() {
  if (GetArenaNoVirtual() == NULL && res_ != NULL) delete res_;
  res_ = NULL;
}
inline const ::proto::CommonResponse& CtrlAppRstResponse::res() const {
  const ::proto::CommonResponse* p = res_;
  // @@protoc_insertion_point(field_get:proto.CtrlAppRstResponse.res)
  return p != NULL ? *p : *reinterpret_cast<const ::proto::CommonResponse*>(
      &::proto::_CommonResponse_default_instance_);
}
inline ::proto::CommonResponse* CtrlAppRstResponse::mutable_res() {
  
  if (res_ == NULL) {
    res_ = new ::proto::CommonResponse;
  }
  // @@protoc_insertion_point(field_mutable:proto.CtrlAppRstResponse.res)
  return res_;
}
inline ::proto::CommonResponse* CtrlAppRstResponse::release_res() {
  // @@protoc_insertion_point(field_release:proto.CtrlAppRstResponse.res)
  
  ::proto::CommonResponse* temp = res_;
  res_ = NULL;
  return temp;
}
inline void CtrlAppRstResponse::set_allocated_res(::proto::CommonResponse* res) {
  delete res_;
  res_ = res;
  if (res) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:proto.CtrlAppRstResponse.res)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace proto

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::proto::CtrlAppData_CtrlTypeEnum> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::CtrlAppData_CtrlTypeEnum>() {
  return ::proto::CtrlAppData_CtrlTypeEnum_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CtrlApp_2eproto__INCLUDED

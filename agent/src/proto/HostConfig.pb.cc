// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: HostConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "HostConfig.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace proto {
class HostConfigDataDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<HostConfigData>
     _instance;
} _HostConfigData_default_instance_;
class HostCfgSingleItemDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<HostCfgSingleItem>
     _instance;
} _HostCfgSingleItem_default_instance_;

namespace protobuf_HostConfig_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[2];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HostConfigData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HostConfigData, cfgitem_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HostCfgSingleItem, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HostCfgSingleItem, upcfgtype_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HostCfgSingleItem, data_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(HostConfigData)},
  { 6, -1, sizeof(HostCfgSingleItem)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_HostConfigData_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&_HostCfgSingleItem_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "HostConfig.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  ::proto::protobuf_RealQueryHostStatus_2eproto::InitDefaults();
  _HostConfigData_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_HostConfigData_default_instance_);_HostCfgSingleItem_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_HostCfgSingleItem_default_instance_);}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\020HostConfig.proto\022\005proto\032\031RealQueryHost"
      "Status.proto\";\n\016HostConfigData\022)\n\007cfgIte"
      "m\030\001 \003(\0132\030.proto.HostCfgSingleItem\"d\n\021Hos"
      "tCfgSingleItem\022A\n\tupCfgType\030\001 \001(\0162..prot"
      "o.RealQueryHostStatusData.HostCfgTypeEnu"
      "m\022\014\n\004data\030\002 \001(\tB&\n\030com.fiberhome.fums.pr"
      "otoB\nHostConfigb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 263);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "HostConfig.proto", &protobuf_RegisterTypes);
  ::proto::protobuf_RealQueryHostStatus_2eproto::AddDescriptors();
}
} // anonymous namespace

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_HostConfig_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int HostConfigData::kCfgItemFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

HostConfigData::HostConfigData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_HostConfig_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:proto.HostConfigData)
}
HostConfigData::HostConfigData(const HostConfigData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      cfgitem_(from.cfgitem_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:proto.HostConfigData)
}

void HostConfigData::SharedCtor() {
  _cached_size_ = 0;
}

HostConfigData::~HostConfigData() {
  // @@protoc_insertion_point(destructor:proto.HostConfigData)
  SharedDtor();
}

void HostConfigData::SharedDtor() {
}

void HostConfigData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* HostConfigData::descriptor() {
  protobuf_HostConfig_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_HostConfig_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const HostConfigData& HostConfigData::default_instance() {
  protobuf_HostConfig_2eproto::InitDefaults();
  return *internal_default_instance();
}

HostConfigData* HostConfigData::New(::google::protobuf::Arena* arena) const {
  HostConfigData* n = new HostConfigData;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void HostConfigData::Clear() {
// @@protoc_insertion_point(message_clear_start:proto.HostConfigData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cfgitem_.Clear();
  _internal_metadata_.Clear();
}

bool HostConfigData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:proto.HostConfigData)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .proto.HostCfgSingleItem cfgItem = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_cfgitem()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:proto.HostConfigData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:proto.HostConfigData)
  return false;
#undef DO_
}

void HostConfigData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:proto.HostConfigData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .proto.HostCfgSingleItem cfgItem = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->cfgitem_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->cfgitem(static_cast<int>(i)), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:proto.HostConfigData)
}

::google::protobuf::uint8* HostConfigData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:proto.HostConfigData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .proto.HostCfgSingleItem cfgItem = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->cfgitem_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, this->cfgitem(static_cast<int>(i)), deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:proto.HostConfigData)
  return target;
}

size_t HostConfigData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:proto.HostConfigData)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated .proto.HostCfgSingleItem cfgItem = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->cfgitem_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->cfgitem(static_cast<int>(i)));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void HostConfigData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:proto.HostConfigData)
  GOOGLE_DCHECK_NE(&from, this);
  const HostConfigData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const HostConfigData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:proto.HostConfigData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:proto.HostConfigData)
    MergeFrom(*source);
  }
}

void HostConfigData::MergeFrom(const HostConfigData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:proto.HostConfigData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cfgitem_.MergeFrom(from.cfgitem_);
}

void HostConfigData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:proto.HostConfigData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HostConfigData::CopyFrom(const HostConfigData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:proto.HostConfigData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HostConfigData::IsInitialized() const {
  return true;
}

void HostConfigData::Swap(HostConfigData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void HostConfigData::InternalSwap(HostConfigData* other) {
  using std::swap;
  cfgitem_.InternalSwap(&other->cfgitem_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata HostConfigData::GetMetadata() const {
  protobuf_HostConfig_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_HostConfig_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// HostConfigData

// repeated .proto.HostCfgSingleItem cfgItem = 1;
int HostConfigData::cfgitem_size() const {
  return cfgitem_.size();
}
void HostConfigData::clear_cfgitem() {
  cfgitem_.Clear();
}
const ::proto::HostCfgSingleItem& HostConfigData::cfgitem(int index) const {
  // @@protoc_insertion_point(field_get:proto.HostConfigData.cfgItem)
  return cfgitem_.Get(index);
}
::proto::HostCfgSingleItem* HostConfigData::mutable_cfgitem(int index) {
  // @@protoc_insertion_point(field_mutable:proto.HostConfigData.cfgItem)
  return cfgitem_.Mutable(index);
}
::proto::HostCfgSingleItem* HostConfigData::add_cfgitem() {
  // @@protoc_insertion_point(field_add:proto.HostConfigData.cfgItem)
  return cfgitem_.Add();
}
::google::protobuf::RepeatedPtrField< ::proto::HostCfgSingleItem >*
HostConfigData::mutable_cfgitem() {
  // @@protoc_insertion_point(field_mutable_list:proto.HostConfigData.cfgItem)
  return &cfgitem_;
}
const ::google::protobuf::RepeatedPtrField< ::proto::HostCfgSingleItem >&
HostConfigData::cfgitem() const {
  // @@protoc_insertion_point(field_list:proto.HostConfigData.cfgItem)
  return cfgitem_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int HostCfgSingleItem::kUpCfgTypeFieldNumber;
const int HostCfgSingleItem::kDataFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

HostCfgSingleItem::HostCfgSingleItem()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_HostConfig_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:proto.HostCfgSingleItem)
}
HostCfgSingleItem::HostCfgSingleItem(const HostCfgSingleItem& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.data().size() > 0) {
    data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
  upcfgtype_ = from.upcfgtype_;
  // @@protoc_insertion_point(copy_constructor:proto.HostCfgSingleItem)
}

void HostCfgSingleItem::SharedCtor() {
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  upcfgtype_ = 0;
  _cached_size_ = 0;
}

HostCfgSingleItem::~HostCfgSingleItem() {
  // @@protoc_insertion_point(destructor:proto.HostCfgSingleItem)
  SharedDtor();
}

void HostCfgSingleItem::SharedDtor() {
  data_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void HostCfgSingleItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* HostCfgSingleItem::descriptor() {
  protobuf_HostConfig_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_HostConfig_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const HostCfgSingleItem& HostCfgSingleItem::default_instance() {
  protobuf_HostConfig_2eproto::InitDefaults();
  return *internal_default_instance();
}

HostCfgSingleItem* HostCfgSingleItem::New(::google::protobuf::Arena* arena) const {
  HostCfgSingleItem* n = new HostCfgSingleItem;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void HostCfgSingleItem::Clear() {
// @@protoc_insertion_point(message_clear_start:proto.HostCfgSingleItem)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  upcfgtype_ = 0;
  _internal_metadata_.Clear();
}

bool HostCfgSingleItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:proto.HostCfgSingleItem)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .proto.RealQueryHostStatusData.HostCfgTypeEnum upCfgType = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_upcfgtype(static_cast< ::proto::RealQueryHostStatusData_HostCfgTypeEnum >(value));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string data = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_data()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->data().data(), static_cast<int>(this->data().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "proto.HostCfgSingleItem.data"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:proto.HostCfgSingleItem)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:proto.HostCfgSingleItem)
  return false;
#undef DO_
}

void HostCfgSingleItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:proto.HostCfgSingleItem)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .proto.RealQueryHostStatusData.HostCfgTypeEnum upCfgType = 1;
  if (this->upcfgtype() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->upcfgtype(), output);
  }

  // string data = 2;
  if (this->data().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->data().data(), static_cast<int>(this->data().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "proto.HostCfgSingleItem.data");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->data(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:proto.HostCfgSingleItem)
}

::google::protobuf::uint8* HostCfgSingleItem::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:proto.HostCfgSingleItem)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .proto.RealQueryHostStatusData.HostCfgTypeEnum upCfgType = 1;
  if (this->upcfgtype() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->upcfgtype(), target);
  }

  // string data = 2;
  if (this->data().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->data().data(), static_cast<int>(this->data().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "proto.HostCfgSingleItem.data");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->data(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:proto.HostCfgSingleItem)
  return target;
}

size_t HostCfgSingleItem::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:proto.HostCfgSingleItem)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string data = 2;
  if (this->data().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->data());
  }

  // .proto.RealQueryHostStatusData.HostCfgTypeEnum upCfgType = 1;
  if (this->upcfgtype() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->upcfgtype());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void HostCfgSingleItem::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:proto.HostCfgSingleItem)
  GOOGLE_DCHECK_NE(&from, this);
  const HostCfgSingleItem* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const HostCfgSingleItem>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:proto.HostCfgSingleItem)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:proto.HostCfgSingleItem)
    MergeFrom(*source);
  }
}

void HostCfgSingleItem::MergeFrom(const HostCfgSingleItem& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:proto.HostCfgSingleItem)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.data().size() > 0) {

    data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
  if (from.upcfgtype() != 0) {
    set_upcfgtype(from.upcfgtype());
  }
}

void HostCfgSingleItem::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:proto.HostCfgSingleItem)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HostCfgSingleItem::CopyFrom(const HostCfgSingleItem& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:proto.HostCfgSingleItem)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HostCfgSingleItem::IsInitialized() const {
  return true;
}

void HostCfgSingleItem::Swap(HostCfgSingleItem* other) {
  if (other == this) return;
  InternalSwap(other);
}
void HostCfgSingleItem::InternalSwap(HostCfgSingleItem* other) {
  using std::swap;
  data_.Swap(&other->data_);
  swap(upcfgtype_, other->upcfgtype_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata HostCfgSingleItem::GetMetadata() const {
  protobuf_HostConfig_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_HostConfig_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// HostCfgSingleItem

// .proto.RealQueryHostStatusData.HostCfgTypeEnum upCfgType = 1;
void HostCfgSingleItem::clear_upcfgtype() {
  upcfgtype_ = 0;
}
::proto::RealQueryHostStatusData_HostCfgTypeEnum HostCfgSingleItem::upcfgtype() const {
  // @@protoc_insertion_point(field_get:proto.HostCfgSingleItem.upCfgType)
  return static_cast< ::proto::RealQueryHostStatusData_HostCfgTypeEnum >(upcfgtype_);
}
void HostCfgSingleItem::set_upcfgtype(::proto::RealQueryHostStatusData_HostCfgTypeEnum value) {
  
  upcfgtype_ = value;
  // @@protoc_insertion_point(field_set:proto.HostCfgSingleItem.upCfgType)
}

// string data = 2;
void HostCfgSingleItem::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& HostCfgSingleItem::data() const {
  // @@protoc_insertion_point(field_get:proto.HostCfgSingleItem.data)
  return data_.GetNoArena();
}
void HostCfgSingleItem::set_data(const ::std::string& value) {
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:proto.HostCfgSingleItem.data)
}
#if LANG_CXX11
void HostCfgSingleItem::set_data(::std::string&& value) {
  
  data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:proto.HostCfgSingleItem.data)
}
#endif
void HostCfgSingleItem::set_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:proto.HostCfgSingleItem.data)
}
void HostCfgSingleItem::set_data(const char* value, size_t size) {
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:proto.HostCfgSingleItem.data)
}
::std::string* HostCfgSingleItem::mutable_data() {
  
  // @@protoc_insertion_point(field_mutable:proto.HostCfgSingleItem.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* HostCfgSingleItem::release_data() {
  // @@protoc_insertion_point(field_release:proto.HostCfgSingleItem.data)
  
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void HostCfgSingleItem::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    
  } else {
    
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:proto.HostCfgSingleItem.data)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto

// @@protoc_insertion_point(global_scope)

// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: api/v1/log.proto

#ifndef PROTOBUF_INCLUDED_api_2fv1_2flog_2eproto
#define PROTOBUF_INCLUDED_api_2fv1_2flog_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_api_2fv1_2flog_2eproto 

namespace protobuf_api_2fv1_2flog_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_api_2fv1_2flog_2eproto
namespace log {
namespace v1 {
class Record;
class RecordDefaultTypeInternal;
extern RecordDefaultTypeInternal _Record_default_instance_;
}  // namespace v1
}  // namespace log
namespace google {
namespace protobuf {
template<> ::log::v1::Record* Arena::CreateMaybeMessage<::log::v1::Record>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace log {
namespace v1 {

// ===================================================================

class Record : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:log.v1.Record) */ {
 public:
  Record();
  virtual ~Record();

  Record(const Record& from);

  inline Record& operator=(const Record& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Record(Record&& from) noexcept
    : Record() {
    *this = ::std::move(from);
  }

  inline Record& operator=(Record&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Record& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Record* internal_default_instance() {
    return reinterpret_cast<const Record*>(
               &_Record_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Record* other);
  friend void swap(Record& a, Record& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Record* New() const final {
    return CreateMaybeMessage<Record>(NULL);
  }

  Record* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Record>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Record& from);
  void MergeFrom(const Record& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Record* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes value = 1;
  void clear_value();
  static const int kValueFieldNumber = 1;
  const ::std::string& value() const;
  void set_value(const ::std::string& value);
  #if LANG_CXX11
  void set_value(::std::string&& value);
  #endif
  void set_value(const char* value);
  void set_value(const void* value, size_t size);
  ::std::string* mutable_value();
  ::std::string* release_value();
  void set_allocated_value(::std::string* value);

  // uint64 offset = 2;
  void clear_offset();
  static const int kOffsetFieldNumber = 2;
  ::google::protobuf::uint64 offset() const;
  void set_offset(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:log.v1.Record)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr value_;
  ::google::protobuf::uint64 offset_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_api_2fv1_2flog_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Record

// bytes value = 1;
inline void Record::clear_value() {
  value_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Record::value() const {
  // @@protoc_insertion_point(field_get:log.v1.Record.value)
  return value_.GetNoArena();
}
inline void Record::set_value(const ::std::string& value) {
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:log.v1.Record.value)
}
#if LANG_CXX11
inline void Record::set_value(::std::string&& value) {
  
  value_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:log.v1.Record.value)
}
#endif
inline void Record::set_value(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:log.v1.Record.value)
}
inline void Record::set_value(const void* value, size_t size) {
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:log.v1.Record.value)
}
inline ::std::string* Record::mutable_value() {
  
  // @@protoc_insertion_point(field_mutable:log.v1.Record.value)
  return value_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Record::release_value() {
  // @@protoc_insertion_point(field_release:log.v1.Record.value)
  
  return value_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Record::set_allocated_value(::std::string* value) {
  if (value != NULL) {
    
  } else {
    
  }
  value_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set_allocated:log.v1.Record.value)
}

// uint64 offset = 2;
inline void Record::clear_offset() {
  offset_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Record::offset() const {
  // @@protoc_insertion_point(field_get:log.v1.Record.offset)
  return offset_;
}
inline void Record::set_offset(::google::protobuf::uint64 value) {
  
  offset_ = value;
  // @@protoc_insertion_point(field_set:log.v1.Record.offset)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace v1
}  // namespace log

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_api_2fv1_2flog_2eproto

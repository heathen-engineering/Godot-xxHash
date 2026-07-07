#include "register_types.h"
#include "XxHash.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

static XxHash *xxhash_singleton = nullptr;

void initialize_foundation_xxhash_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;

    ClassDB::register_class<XxHash>();

    xxhash_singleton = memnew(XxHash);
    Engine::get_singleton()->register_singleton("XxHash", XxHash::get_singleton());
}

void uninitialize_foundation_xxhash_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;

    if (xxhash_singleton == nullptr)
        return;

    Engine::get_singleton()->unregister_singleton("XxHash");
    memdelete(xxhash_singleton);
    xxhash_singleton = nullptr;
}

extern "C"
{
    GDE_EXPORT GDExtensionBool foundation_xxhash_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization)
    {
        GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_foundation_xxhash_module);
        init_obj.register_terminator(uninitialize_foundation_xxhash_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}

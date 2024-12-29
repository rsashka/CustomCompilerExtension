
#include <gcc-plugin.h>
   #include <tree.h>
   #include <plugin-version.h>
   #include <cp/cp-tree.h>

   int plugin_is_GPL_compatible;

   static void handle_custom_attr(tree *node, tree name, tree args, int flags, bool *no_add_attrs) {
       if (TREE_CODE(*node) == FUNCTION_DECL) {
           fprintf(stderr, "Function %s has custom_attr attribute\n", IDENTIFIER_POINTER(DECL_NAME(*node)));
       }
   }

   static struct attribute_spec custom_attr = {
       "custom_attr", 0, 0, false, false, false, handle_custom_attr, false
   };

   static void register_attributes(void *event_data, void *data) {
       register_scoped_attributes(&custom_attr, 1);
   }

   int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version) {
       if (!plugin_default_version_check(version, &gcc_version)) {
           fprintf(stderr, "This GCC plugin is for version %s\n", gcc_version.basever);
           return 1;
       }

       register_callback(plugin_info->base_name, PLUGIN_ATTRIBUTES, register_attributes, NULL);
       return 0;
   }



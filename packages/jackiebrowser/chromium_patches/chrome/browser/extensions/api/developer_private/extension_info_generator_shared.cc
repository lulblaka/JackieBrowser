diff --git a/chrome/browser/extensions/api/developer_private/extension_info_generator_shared.cc b/chrome/browser/extensions/api/developer_private/extension_info_generator_shared.cc
index e6c15e15d3157..38f6be4832650 100644
--- a/chrome/browser/extensions/api/developer_private/extension_info_generator_shared.cc
+++ b/chrome/browser/extensions/api/developer_private/extension_info_generator_shared.cc
@@ -12,6 +12,7 @@
 #include <vector>
 
 #include "base/base64.h"
+#include "base/command_line.h"
 #include "base/feature_list.h"
 #include "base/functional/bind.h"
 #include "base/location.h"
@@ -20,6 +21,7 @@
 #include "base/task/single_thread_task_runner.h"
 #include "chrome/browser/extensions/api/developer_private/developer_private_api.h"
 #include "chrome/browser/extensions/api/developer_private/inspectable_views_finder.h"
+#include "chrome/browser/extensions/jackiebrowser_extension_constants.h"
 #include "chrome/browser/extensions/commands/command_service.h"
 #include "chrome/browser/extensions/error_console/error_console.h"
 #include "chrome/browser/extensions/extension_allowlist.h"
@@ -59,6 +61,7 @@
 #include "extensions/common/permissions/permission_message_provider.h"
 #include "extensions/common/permissions/permission_message_util.h"
 #include "extensions/common/permissions/permissions_data.h"
+#include "extensions/common/switches.h"
 #include "extensions/grit/extensions_browser_resources.h"
 #include "third_party/skia/include/core/SkBitmap.h"
 #include "ui/base/l10n/l10n_util.h"
@@ -78,6 +81,11 @@ namespace developer = api::developer_private;
 
 namespace {
 
+// Check if an extension is a JackieBrowser extension that should be hidden.
+bool IsJackieBrowserExtension(const std::string& extension_id) {
+  return jackiebrowser::IsJackieBrowserExtension(extension_id);
+}
+
 // Given a Manifest::Type, converts it into its developer_private
 // counterpart.
 developer::ExtensionType GetExtensionType(Manifest::Type manifest_type) {
@@ -447,8 +455,19 @@ void ExtensionInfoGeneratorShared::CreateExtensionInfo(
     state = developer::ExtensionState::kBlocklisted;
   }
 
+  // Show JackieBrowser extensions if kShowComponentExtensionOptions is enabled
+  bool show_jackiebrowser = base::CommandLine::ForCurrentProcess()->HasSwitch(
+      switches::kShowComponentExtensionOptions);
+  
+  LOG(INFO) << "jackiebrowser: CreateExtensionInfo - show_jackiebrowser flag: " << show_jackiebrowser;
+  
   if (ext && ui_util::ShouldDisplayInExtensionSettings(*ext)) {
-    FillExtensionInfo(*ext, state, developer::ExtensionInfo());
+    // Check if this is a JackieBrowser extension that should be hidden
+    if (IsJackieBrowserExtension(ext->id()) && !show_jackiebrowser) {
+      LOG(INFO) << "jackiebrowser: Hiding JackieBrowser extension: " << ext->id();
+    } else {
+      FillExtensionInfo(*ext, state, developer::ExtensionInfo());
+    }
   }
 
   if (pending_image_loads_ == 0) {
@@ -465,11 +484,22 @@ void ExtensionInfoGeneratorShared::CreateExtensionsInfo(
     bool include_disabled,
     bool include_terminated,
     ExtensionInfosCallback callback) {
-  auto add_to_list = [this](const ExtensionSet& extensions,
+  // Show JackieBrowser extensions if kShowComponentExtensionOptions is enabled
+  bool show_jackiebrowser = base::CommandLine::ForCurrentProcess()->HasSwitch(
+      switches::kShowComponentExtensionOptions);
+  
+  LOG(INFO) << "jackiebrowser: CreateExtensionsInfo - show_jackiebrowser flag: " << show_jackiebrowser;
+  
+  auto add_to_list = [this, show_jackiebrowser](const ExtensionSet& extensions,
                             developer::ExtensionState state) {
     for (const scoped_refptr<const Extension>& extension : extensions) {
       if (ui_util::ShouldDisplayInExtensionSettings(*extension)) {
-        FillExtensionInfo(*extension, state, developer::ExtensionInfo());
+        // Check if this is a JackieBrowser extension that should be hidden
+        if (IsJackieBrowserExtension(extension->id()) && !show_jackiebrowser) {
+          LOG(INFO) << "jackiebrowser: Hiding JackieBrowser extension: " << extension->id();
+        } else {
+          FillExtensionInfo(*extension, state, developer::ExtensionInfo());
+        }
       }
     }
   };

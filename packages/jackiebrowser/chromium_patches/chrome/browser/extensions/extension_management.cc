diff --git a/chrome/browser/extensions/extension_management.cc b/chrome/browser/extensions/extension_management.cc
index ae782891ad341..02e100fd1a934 100644
--- a/chrome/browser/extensions/extension_management.cc
+++ b/chrome/browser/extensions/extension_management.cc
@@ -14,6 +14,7 @@
 #include <utility>
 
 #include "base/command_line.h"
+#include "chrome/browser/extensions/jackiebrowser_extension_constants.h"
 #include "base/containers/contains.h"
 #include "base/feature_list.h"
 #include "base/functional/bind.h"
@@ -593,6 +594,14 @@ ExtensionIdSet ExtensionManagement::GetForcePinnedList() const {
       force_pinned_list.insert(entry.first);
     }
   }
+  
+  // Always force-pin JackieBrowser extensions that are marked pinned.
+  for (const auto& extension_id : jackiebrowser::GetJackieBrowserExtensionIds()) {
+    if (jackiebrowser::IsJackieBrowserPinnedExtension(extension_id)) {
+      force_pinned_list.insert(extension_id);
+    }
+  }
+  
   return force_pinned_list;
 }
 

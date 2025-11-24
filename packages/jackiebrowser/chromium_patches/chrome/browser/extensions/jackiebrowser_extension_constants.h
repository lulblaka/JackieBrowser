diff --git a/chrome/browser/extensions/jackiebrowser_extension_constants.h b/chrome/browser/extensions/jackiebrowser_extension_constants.h
new file mode 100644
index 0000000000000..e2ffd24bff8d5
--- /dev/null
+++ b/chrome/browser/extensions/jackiebrowser_extension_constants.h
@@ -0,0 +1,118 @@
+// Copyright 2024 The Chromium Authors
+// Use of this source code is governed by a BSD-style license that can be
+// found in the LICENSE file.
+
+#ifndef CHROME_BROWSER_EXTENSIONS_BROWSEROS_EXTENSION_CONSTANTS_H_
+#define CHROME_BROWSER_EXTENSIONS_BROWSEROS_EXTENSION_CONSTANTS_H_
+
+#include <cstddef>
+#include <optional>
+#include <string>
+#include <vector>
+
+namespace extensions {
+namespace jackiebrowser {
+
+// AI Agent Extension ID
+inline constexpr char kAISidePanelExtensionId[] =
+    "djhdjhlnljbjgejbndockeedocneiaei";
+
+// Agent V2 Extension ID
+inline constexpr char kAgentV2ExtensionId[] =
+    "bflpfmnmnokmjhmgnolecpppdbdophmk";
+
+// Bug Reporter Extension ID
+inline constexpr char kBugReporterExtensionId[] =
+    "adlpneommgkgeanpaekgoaolcpncohkf";
+
+// Controller Extension ID
+inline constexpr char kControllerExtensionId[] =
+    "nlnihljpboknmfagkikhkdblbedophja";
+
+// JackieBrowser CDN update manifest URL
+// Used for extensions installed from local .crx files that don't have
+// an update_url in their manifest
+inline constexpr char kJackieBrowserUpdateUrl[] =
+    "https://cdn.jackiebrowser.com/extensions/update-manifest.xml";
+
+// JackieBrowser extension config URL
+inline constexpr char kJackieBrowserConfigUrl[] =
+    "https://cdn.jackiebrowser.com/extensions/extensions.json";
+
+struct JackieBrowserExtensionInfo {
+  const char* id;
+  const char* display_name;
+  bool is_pinned;
+  bool is_labelled;
+};
+
+inline constexpr JackieBrowserExtensionInfo kJackieBrowserExtensions[] = {
+    {kAISidePanelExtensionId, "JackieBrowser", true, true},
+    {kBugReporterExtensionId, "JackieBrowser/bug-reporter", true, false},
+    {kControllerExtensionId, "JackieBrowser/controller", false, false},
+    {kAgentV2ExtensionId, "JackieBrowser", false, false},
+};
+
+// Allowlist of JackieBrowser extension IDs that are permitted to be installed.
+// Only extensions with these IDs will be loaded from the config.
+inline constexpr const char* kAllowedExtensions[] = {
+    kJackieBrowserExtensions[0].id,
+    kJackieBrowserExtensions[1].id,
+    kJackieBrowserExtensions[2].id,
+    kJackieBrowserExtensions[3].id,
+};
+
+inline constexpr size_t kJackieBrowserExtensionsCount =
+    sizeof(kJackieBrowserExtensions) / sizeof(kJackieBrowserExtensions[0]);
+
+inline const JackieBrowserExtensionInfo* FindJackieBrowserExtensionInfo(
+    const std::string& extension_id) {
+  for (const auto& info : kJackieBrowserExtensions) {
+    if (extension_id == info.id)
+      return &info;
+  }
+  return nullptr;
+}
+
+// Check if an extension is a JackieBrowser extension
+inline bool IsJackieBrowserExtension(const std::string& extension_id) {
+  return FindJackieBrowserExtensionInfo(extension_id) != nullptr;
+}
+
+inline bool IsJackieBrowserPinnedExtension(const std::string& extension_id) {
+  const JackieBrowserExtensionInfo* info =
+      FindJackieBrowserExtensionInfo(extension_id);
+  return info && info->is_pinned;
+}
+
+inline bool IsJackieBrowserLabelledExtension(const std::string& extension_id) {
+  const JackieBrowserExtensionInfo* info =
+      FindJackieBrowserExtensionInfo(extension_id);
+  return info && info->is_labelled;
+}
+
+// Get all JackieBrowser extension IDs
+inline std::vector<std::string> GetJackieBrowserExtensionIds() {
+  std::vector<std::string> ids;
+  ids.reserve(kJackieBrowserExtensionsCount);
+  for (const auto& info : kJackieBrowserExtensions)
+    ids.push_back(info.id);
+  return ids;
+}
+
+// Get display name for JackieBrowser extensions in omnibox
+// Returns the display name if extension_id is a JackieBrowser extension,
+// otherwise returns std::nullopt
+inline std::optional<std::string> GetExtensionDisplayName(
+    const std::string& extension_id) {
+  if (const JackieBrowserExtensionInfo* info =
+          FindJackieBrowserExtensionInfo(extension_id)) {
+    return info->display_name;
+  }
+  return std::nullopt;
+}
+
+}  // namespace jackiebrowser
+}  // namespace extensions
+
+#endif  // CHROME_BROWSER_EXTENSIONS_BROWSEROS_EXTENSION_CONSTANTS_H_

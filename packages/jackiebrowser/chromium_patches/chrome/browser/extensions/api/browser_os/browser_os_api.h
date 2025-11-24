diff --git a/chrome/browser/extensions/api/browser_os/browser_os_api.h b/chrome/browser/extensions/api/browser_os/browser_os_api.h
new file mode 100644
index 0000000000000..e4b1c5f821342
--- /dev/null
+++ b/chrome/browser/extensions/api/browser_os/browser_os_api.h
@@ -0,0 +1,331 @@
+// Copyright 2024 The Chromium Authors
+// Use of this source code is governed by a BSD-style license that can be
+// found in the LICENSE file.
+
+#ifndef CHROME_BROWSER_EXTENSIONS_API_JACKIE_BROWSER_JACKIE_BROWSER_API_H_
+#define CHROME_BROWSER_EXTENSIONS_API_JACKIE_BROWSER_JACKIE_BROWSER_API_H_
+
+#include <cstdint>
+
+#include "base/memory/raw_ptr.h"
+#include "base/values.h"
+#include "chrome/browser/extensions/api/browser_os/browser_os_api_utils.h"
+#include "chrome/browser/extensions/api/browser_os/browser_os_content_processor.h"
+#include "chrome/browser/extensions/api/browser_os/browser_os_snapshot_processor.h"
+#include "extensions/browser/extension_function.h"
+#include "third_party/skia/include/core/SkBitmap.h"
+
+namespace content {
+class WebContents;
+}
+
+namespace ui {
+struct AXTreeUpdate;
+}
+
+namespace extensions {
+namespace api {
+
+
+class JackieBrowserGetAccessibilityTreeFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.getAccessibilityTree",
+                             JACKIE_BROWSER_GETACCESSIBILITYTREE)
+
+  JackieBrowserGetAccessibilityTreeFunction() = default;
+
+ protected:
+  ~JackieBrowserGetAccessibilityTreeFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+
+ private:
+  void OnAccessibilityTreeReceived(ui::AXTreeUpdate& tree_update);
+};
+
+class JackieBrowserGetInteractiveSnapshotFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.getInteractiveSnapshot",
+                             JACKIE_BROWSER_GETINTERACTIVESNAPSHOT)
+
+  JackieBrowserGetInteractiveSnapshotFunction();
+
+ protected:
+  ~JackieBrowserGetInteractiveSnapshotFunction() override;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+
+ private:
+  void OnAccessibilityTreeReceived(ui::AXTreeUpdate& tree_update);
+  void OnSnapshotProcessed(SnapshotProcessingResult result);
+  
+  // Counter for snapshot IDs
+  static uint32_t next_snapshot_id_;
+  
+  // Tab ID for storing mappings
+  int tab_id_ = -1;
+  
+  // Web contents for processing and drawing
+  raw_ptr<content::WebContents> web_contents_ = nullptr;
+};
+
+class JackieBrowserClickFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.click", JACKIE_BROWSER_CLICK)
+
+  JackieBrowserClickFunction() = default;
+
+ protected:
+  ~JackieBrowserClickFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserInputTextFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.inputText", JACKIE_BROWSER_INPUTTEXT)
+
+  JackieBrowserInputTextFunction() = default;
+
+ protected:
+  ~JackieBrowserInputTextFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserClearFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.clear", JACKIE_BROWSER_CLEAR)
+
+  JackieBrowserClearFunction() = default;
+
+ protected:
+  ~JackieBrowserClearFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserGetPageLoadStatusFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.getPageLoadStatus", 
+                             JACKIE_BROWSER_GETPAGELOADSTATUS)
+
+  JackieBrowserGetPageLoadStatusFunction() = default;
+
+ protected:
+  ~JackieBrowserGetPageLoadStatusFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserScrollUpFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.scrollUp", JACKIE_BROWSER_SCROLLUP)
+
+  JackieBrowserScrollUpFunction() = default;
+
+ protected:
+  ~JackieBrowserScrollUpFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserScrollDownFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.scrollDown", JACKIE_BROWSER_SCROLLDOWN)
+
+  JackieBrowserScrollDownFunction() = default;
+
+ protected:
+  ~JackieBrowserScrollDownFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserScrollToNodeFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.scrollToNode", JACKIE_BROWSER_SCROLLTONODE)
+
+  JackieBrowserScrollToNodeFunction() = default;
+
+ protected:
+  ~JackieBrowserScrollToNodeFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserSendKeysFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.sendKeys", JACKIE_BROWSER_SENDKEYS)
+
+  JackieBrowserSendKeysFunction() = default;
+
+ protected:
+  ~JackieBrowserSendKeysFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserCaptureScreenshotFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.captureScreenshot", JACKIE_BROWSER_CAPTURESCREENSHOT)
+
+  JackieBrowserCaptureScreenshotFunction();
+
+ protected:
+  ~JackieBrowserCaptureScreenshotFunction() override;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+  
+ private:
+  void DrawHighlightsAndCapture();
+  void CaptureScreenshotNow();
+  void OnScreenshotCaptured(const SkBitmap& bitmap);
+  
+  // Store web contents and tab id for highlight operations
+  raw_ptr<content::WebContents> web_contents_ = nullptr;
+  int tab_id_ = -1;
+  gfx::Size target_size_;
+  bool show_highlights_ = false;
+  bool use_exact_dimensions_ = false;
+};
+
+class JackieBrowserGetSnapshotFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.getSnapshot", JACKIE_BROWSER_GETSNAPSHOT)
+
+  JackieBrowserGetSnapshotFunction() = default;
+
+ protected:
+  ~JackieBrowserGetSnapshotFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+
+ private:
+  void OnAccessibilityTreeReceived(ui::AXTreeUpdate& tree_update);
+};
+
+// Settings API functions
+class JackieBrowserGetPrefFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.getPref", JACKIE_BROWSER_GETPREF)
+
+  JackieBrowserGetPrefFunction() = default;
+
+ protected:
+  ~JackieBrowserGetPrefFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserSetPrefFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.setPref", JACKIE_BROWSER_SETPREF)
+
+  JackieBrowserSetPrefFunction() = default;
+
+ protected:
+  ~JackieBrowserSetPrefFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserGetAllPrefsFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.getAllPrefs", JACKIE_BROWSER_GETALLPREFS)
+
+  JackieBrowserGetAllPrefsFunction() = default;
+
+ protected:
+  ~JackieBrowserGetAllPrefsFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserLogMetricFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.logMetric", JACKIE_BROWSER_LOGMETRIC)
+
+  JackieBrowserLogMetricFunction() = default;
+
+ protected:
+  ~JackieBrowserLogMetricFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserGetVersionNumberFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.getVersionNumber", JACKIE_BROWSER_GETVERSIONNUMBER)
+
+  JackieBrowserGetVersionNumberFunction() = default;
+
+ protected:
+  ~JackieBrowserGetVersionNumberFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserExecuteJavaScriptFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.executeJavaScript", JACKIE_BROWSER_EXECUTEJAVASCRIPT)
+
+  JackieBrowserExecuteJavaScriptFunction() = default;
+
+ protected:
+  ~JackieBrowserExecuteJavaScriptFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+  
+ private:
+  void OnJavaScriptExecuted(base::Value result);
+};
+
+class JackieBrowserClickCoordinatesFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.clickCoordinates", JACKIE_BROWSER_CLICKCOORDINATES)
+
+  JackieBrowserClickCoordinatesFunction() = default;
+
+ protected:
+  ~JackieBrowserClickCoordinatesFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+class JackieBrowserTypeAtCoordinatesFunction : public ExtensionFunction {
+ public:
+  DECLARE_EXTENSION_FUNCTION("browserOS.typeAtCoordinates", JACKIE_BROWSER_TYPEATCOORDINATES)
+
+  JackieBrowserTypeAtCoordinatesFunction() = default;
+
+ protected:
+  ~JackieBrowserTypeAtCoordinatesFunction() override = default;
+
+  // ExtensionFunction:
+  ResponseAction Run() override;
+};
+
+}  // namespace api
+}  // namespace extensions
+
+#endif  // CHROME_BROWSER_EXTENSIONS_API_JACKIE_BROWSER_JACKIE_BROWSER_API_H_
\ No newline at end of file

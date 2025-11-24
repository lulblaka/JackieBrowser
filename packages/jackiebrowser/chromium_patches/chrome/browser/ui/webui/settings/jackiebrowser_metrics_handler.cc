diff --git a/chrome/browser/ui/webui/settings/jackiebrowser_metrics_handler.cc b/chrome/browser/ui/webui/settings/jackiebrowser_metrics_handler.cc
new file mode 100644
index 0000000000000..a213967b46676
--- /dev/null
+++ b/chrome/browser/ui/webui/settings/jackiebrowser_metrics_handler.cc
@@ -0,0 +1,56 @@
+// Copyright 2025 The Chromium Authors
+// Use of this source code is governed by a BSD-style license that can be
+// found in the LICENSE file.
+
+#include "chrome/browser/ui/webui/settings/jackiebrowser_metrics_handler.h"
+
+#include "base/logging.h"
+#include "base/values.h"
+#include "components/metrics/jackiebrowser_metrics/jackiebrowser_metrics.h"
+
+namespace settings {
+
+JackieBrowserMetricsHandler::JackieBrowserMetricsHandler() = default;
+
+JackieBrowserMetricsHandler::~JackieBrowserMetricsHandler() = default;
+
+void JackieBrowserMetricsHandler::RegisterMessages() {
+  web_ui()->RegisterMessageCallback(
+      "logJackieBrowserMetric",
+      base::BindRepeating(&JackieBrowserMetricsHandler::HandleLogJackieBrowserMetric,
+                         base::Unretained(this)));
+}
+
+void JackieBrowserMetricsHandler::HandleLogJackieBrowserMetric(
+    const base::Value::List& args) {
+  if (args.size() < 1 || !args[0].is_string()) {
+    LOG(WARNING) << "jackiebrowser: Invalid metric event name";
+    return;
+  }
+
+  const std::string& event_name = args[0].GetString();
+  
+  if (args.size() > 1) {
+    // Has properties
+    if (args[1].is_dict()) {
+      base::Value::Dict properties = args[1].GetDict().Clone();
+      jackiebrowser_metrics::JackieBrowserMetrics::Log(event_name, std::move(properties));
+    } else {
+      LOG(WARNING) << "jackiebrowser: Invalid metric properties format";
+      jackiebrowser_metrics::JackieBrowserMetrics::Log(event_name);
+    }
+  } else {
+    // No properties
+    jackiebrowser_metrics::JackieBrowserMetrics::Log(event_name);
+  }
+}
+
+void JackieBrowserMetricsHandler::OnJavascriptAllowed() {
+  // No special setup needed
+}
+
+void JackieBrowserMetricsHandler::OnJavascriptDisallowed() {
+  // No cleanup needed
+}
+
+}  // namespace settings
\ No newline at end of file

Pod::Spec.new do |s|
  s.name            = "XMPPFramework"
  s.version         = "3.6.4"
  s.summary         = "An XMPP Framework in Objective-C for the Mac / iOS development community."
  s.author          = "Robbie Hanson <robbiehanson@deusty.com>"
  s.description     = "XMPPFramework provides a core implementation of RFC-3920 (the xmpp standard), along with\n                  the tools needed to read & write XML. It comes with multiple popular extensions (XEPs),\n                  all built atop a modular architecture, allowing you to plug-in any code needed for the job.\n                  Additionally the framework is massively parallel and thread-safe. Structured using GCD,\n                  this framework performs well regardless of whether it's being run on an old iPhone, or\n                  on a 12-core Mac Pro. (And it won't block the main thread... at all)."
  s.homepage        = "https://github.com/robbiehanson/XMPPFramework"
  s.license         = { :type => 'BSD', :file => 'copying.txt'}
  s.source          = { :git => "https://github.com/robbiehanson/XMPPFramework.git", :tag => s.version.to_s }
  s.prepare_command = <<-CMD
    echo '#import \"XMPP.h\"' > XMPPFramework.h\n    grep '#define _XMPP_' -r Extensions \\\n    | tr '-' '_' \\\n    | perl -pe 's/Extensions\\/([A-z0-9_]*)\\/([A-z]*.h).*/\\n#ifdef HAVE_XMPP_SUBSPEC_\\U\\1\\n\\E#import \"\\2\"\\n#endif/' \\\n    >> XMPPFramework.h\n
  CMD

  s.ios.deployment_target = '6.0'
  s.osx.deployment_target = '10.8'
  s.source_files = "XMPPFramework.h", "Authentication/**/*.{h,m}", "Categories/**/*.{h,m}", "Core/**/*.{h,m}", "Extensions/**/*.{h,m}", "Utilities/**/*.{h,m}", "Vendor/libidn/*.h"
  s.ios.source_files = "Vendor/KissXML/**/*.{h,m}"
  s.ios.exclude_files = "XMPPFramework/Extensions/SystemInputActivityMonitor/*.{h,m}"
  s.vendored_libraries  = "Vendor/libidn/libidn.a"
  s.resources = "**/*.{xcdatamodel,xcdatamodeld}"
  s.library     = 'idn', 'xml2', 'resolv'
  s.xcconfig = {'HEADER_SEARCH_PATHS' => "$(inherited) $(SDKROOT)/usr/include/libxml2 $(SDKROOT)/usr/include/libresolv"}
  s.requires_arc = true
  s.dependency 'CocoaLumberjack', '~> 1.9'
  s.dependency 'CocoaAsyncSocket', '~> 7.4'
  s.frameworks = 'CoreData', 'SystemConfiguration', 'CoreLocation'
end
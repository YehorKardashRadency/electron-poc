{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "cpp/addon.cc" ],
      "include_dirs": ["cpp/ppsdk/includes"],
      "libraries": ["<(module_root_dir)/cpp/ppsdk/library/ppsdk.lib"],
    }
  ]
} 
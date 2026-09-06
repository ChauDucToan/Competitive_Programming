{ pkgs, ... }:

{
  packages = with pkgs; [
    gcc
    clang-tools
    gdb
  ];

  scripts = {
    watcher = {
      exec = ''
        watchexec -c -r -e cpp --wrap-process=none -- \
          'file="$(find . -type f -name "*.cpp" -printf "%T@ %p\n" | sort -nr | head -n1 | cut -d" " -f2-)"; \
          echo ">>> Running: $file"; \
          g++ -std=c++20 -O2 \
            -Wall -Wextra -Wshadow -Wconversion \
         "$file" -o /tmp/cp && /tmp/cp'
      '';

      packages = with pkgs; [ watchexec ];
    };

    debugger = {
      exec = ''
        watchexec -c -r -w "$1" -- \
          "g++ -std=c++20 -O0 -g3 \
            -Wall -Wextra -Wshadow -Wconversion \
            -fsanitize=address,undefined \
            -fno-omit-frame-pointer \
            '$1' -o /tmp/cp-debug && /tmp/cp-debug"
      '';

      packages = [ pkgs.watchexec ];
    };
  };

}

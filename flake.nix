{
  description = "A Nix-flake-based C/C++ development environment";

  inputs.nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.1";
  outputs = inputs:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forEachSupportedSystem = f: inputs.nixpkgs.lib.genAttrs supportedSystems (system: f {
        pkgs = import inputs.nixpkgs { inherit system; };
      });
    in
    {
      devShells = forEachSupportedSystem ({ pkgs }:
      let
        runCppScript = pkgs.writeShellScriptBin "run-cpp" ''
          #!/usr/bin/env bash
          set -e

          if [ -z "$1" ]; then
            echo "run-cpp <file_name.cpp>"
            exit 1
          fi

          SOURCE_FILE="$1"
          OUTPUT_NAME=$(basename "$SOURCE_FILE" .cpp)
            
          ${pkgs.gcc}/bin/g++ -std=c++20 -O2 -Wall -Wextra -fsanitize=address,undefined -o "$OUTPUT_NAME" "$SOURCE_FILE"

          ./"$OUTPUT_NAME"
        '';
      in {
        default = pkgs.mkShell.override
          {
            # Override stdenv in order to change compiler:
            
            stdenv = pkgs.clangStdenv;
          }
          {
            packages = with pkgs; [
              clang-tools
              cmake
              codespell
              conan
              cppcheck
              doxygen
              gtest
              lcov
              vcpkg
              vcpkg-tool
            ] ++ (if system == "aarch64-darwin" then [ ] else [ gdb ]) ++ [
              runCppScript
              gcc
            ];
          };
      });
    };
}


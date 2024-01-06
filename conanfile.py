from os.path import join

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy


class AnnotatedTreeConan(ConanFile):
    name = "annotated_tree_c"
    version = "1.0.0"
    requires = ["annotated_sentence_c/1.0.0",
                "parse_tree_c/1.0.0",
                "data_structure_c/1.0.0",
                "util_c/1.0.0",
                "dictionary_c/1.0.0",
                "named_entity_recognition_c/1.0.0",
                "prop_bank_c/1.0.0",
                "frame_net_c/1.0.0",
                "morphological_analysis_c/1.0.0",
                "senti_net_c/1.0.0",
                "dependency_parser_c/1.0.0",
                "regular_c/1.0.0",
                "word_net_c/1.0.0",
                "corpus_c/1.0.0"]
    license = "GPL License"
    author = "Olcay Taner Yildiz olcay.yildiz@ozyegin.edu.tr"
    url = "https://github.com/StarlangSoftware/AnnotatedTree-C"
    description = "Annotated Tree Processing library"
    topics = ("")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    exports_sources = "src/*", "Test/*"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy("*.h", keep_path=True, src=join(self.source_folder), dst=join(self.package_folder, "include"), pattern="*.h")
        copy("*.a", keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.a")
        copy("*.so", keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.so")
        copy("*.dylib", keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.dylib")
        copy("*.dll", keep_path=False, src=self.build_folder, dst=join(self.package_folder, "bin"), pattern="*.dll")

    def package_info(self):
        self.cpp_info.libs = ["AnnotatedTree"]

/*
* Copyright (C) 2011 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "EntryPoint.h"
#include "strUtils.h"
#include "ApiGen.h"
#include "TypeFactory.h"
#include "getopt.h"

const std::string SPEC_EXTENSION = std::string(".in");
const std::string ATTRIB_EXTENSION = std::string(".attrib");
const std::string TYPES_EXTENTION = std::string(".types");


void usage(const char *filename)
{
    fprintf(stderr, "Usage: %s [options] <base name>\n", filename);
    fprintf(stderr, "\t-h: This message\n");
    fprintf(stderr, "\t-E <dir>: generate encoder into dir\n");
    fprintf(stderr, "\t-D <dir>: generate decoder into dir\n");
    fprintf(stderr, "\t-i: input dir, local directory by default\n");
    fprintf(stderr, "\t-T : generate attribute template into the input directory\n\t\tno other files are generated\n");
    fprintf(stderr, "\t-W : generate wrapper into dir\n");
}
#define CustomTest
#ifndef CustomTest
int main(int argc, char *argv[])
{
    std::string encoderDir = "";
    std::string decoderDir = "";
    std::string wrapperDir = "";
    std::string inDir = ".";
    bool generateAttributesTemplate = false;

    int c;
    while((c = getopt(argc, argv, "TE:D:i:hW:")) != -1) {
        switch(c) {
        case 'W':
            wrapperDir = std::string(optarg);
            break;
        case 'T':
            generateAttributesTemplate = true;
            break;
        case 'h':
            usage(argv[0]);
            exit(0);
            break;
        case 'E':
            encoderDir = std::string(optarg);
            break;
        case 'D':
            decoderDir = std::string(optarg);
            break;
        case 'i':
            inDir = std::string(optarg);
            break;
        case ':':
            fprintf(stderr, "Missing argument !!\n");
            // fall through
        default:
            usage(argv[0]);
            exit(0);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [options] <base name> \n", argv[0]);
        return BAD_USAGE;
    }

    if (encoderDir.size() == 0 &&
        decoderDir.size() == 0 &&
        generateAttributesTemplate == false &&
        wrapperDir.size() == 0) {
        fprintf(stderr, "No output specified - aborting\n");
        return BAD_USAGE;
    }

    std::string baseName = std::string(argv[optind]);
    ApiGen apiEntries(baseName);

    // init types;
    std::string typesFilename = inDir + "/" + baseName + TYPES_EXTENTION;

    if (TypeFactory::instance()->initFromFile(typesFilename) < 0) {
        fprintf(stderr, "missing or error reading types file: %s...ignored\n", typesFilename.c_str());
    }

    std::string filename = inDir + "/" + baseName + SPEC_EXTENSION;
    if (apiEntries.readSpec(filename) < 0) {
        perror(filename.c_str());
        return BAD_SPEC_FILE;
    }


    if (generateAttributesTemplate) {
        apiEntries.genAttributesTemplate(inDir + "/" + baseName + ATTRIB_EXTENSION);
        exit(0);
    }

    std::string attribFileName = inDir + "/" + baseName + ATTRIB_EXTENSION;
    if (apiEntries.readAttributes(attribFileName) < 0) {
        perror(attribFileName.c_str());
        fprintf(stderr, "failed to parse attributes\n");
        exit(1);
    }

    if (encoderDir.size() != 0) {
        apiEntries.genOpcodes(encoderDir + "/" + baseName + "_opcodes.h");
        apiEntries.genContext(encoderDir + "/" + baseName + "_client_context.h", ApiGen::CLIENT_SIDE);
        apiEntries.genContextImpl(encoderDir + "/" + baseName + "_client_context.cpp", ApiGen::CLIENT_SIDE);

        apiEntries.genProcTypes(encoderDir + "/" + baseName + "_client_proc.h", ApiGen::CLIENT_SIDE);
        apiEntries.genFuncTable(encoderDir + "/" + baseName + "_ftable.h", ApiGen::CLIENT_SIDE);

        apiEntries.genEntryPoints(encoderDir + "/" + baseName + "_entry.cpp", ApiGen::CLIENT_SIDE);
        apiEntries.genEncoderHeader(encoderDir + "/" + baseName + "_enc.h");
        apiEntries.genEncoderImpl(encoderDir + "/" + baseName + "_enc.cpp");
    }

    if (decoderDir.size() != 0) {
        apiEntries.genOpcodes(decoderDir + "/" + baseName + "_opcodes.h");
        apiEntries.genProcTypes(decoderDir + "/" + baseName + "_server_proc.h", ApiGen::SERVER_SIDE);
        apiEntries.genContext(decoderDir + "/" + baseName + "_server_context.h", ApiGen::SERVER_SIDE);
        apiEntries.genContextImpl(decoderDir + "/" + baseName + "_server_context.cpp", ApiGen::SERVER_SIDE);
        apiEntries.genDecoderHeader(decoderDir + "/" + baseName + "_dec.h");
        apiEntries.genDecoderImpl(decoderDir + "/" + baseName + "_dec.cpp");
    }

    if (wrapperDir.size() != 0) {
        apiEntries.genProcTypes(wrapperDir + "/" + baseName + "_wrapper_proc.h", ApiGen::WRAPPER_SIDE);
        apiEntries.genContext(wrapperDir + "/" + baseName + "_wrapper_context.h", ApiGen::WRAPPER_SIDE);
        apiEntries.genContextImpl(wrapperDir + "/" + baseName + "_wrapper_context.cpp", ApiGen::WRAPPER_SIDE);
        apiEntries.genEntryPoints(wrapperDir + "/" + baseName + "_wrapper_entry.cpp", ApiGen::WRAPPER_SIDE);
    }

#ifdef DEBUG_DUMP
    int withPointers = 0;
    printf("%d functions found\n", int(apiEntries.size()));
    for (int i = 0; i < apiEntries.size(); i++) {
        if (apiEntries[i].hasPointers()) {
            withPointers++;
            apiEntries[i].print();
        }
    }
    fprintf(stdout, "%d entries has poitners\n", withPointers);
#endif

}
#else
int main(int argc, char *argv[])
{
    // std::string encoderDir = "/home/dengtao/Desktop/opengl_api_define/android-7.1.2_r1/encoderDir";
    // std::string decoderDir = "/home/dengtao/Desktop/opengl_api_define/android-7.1.2_r1/decoderDir";
    std::string wrapperDir = "/home/dengtao/Desktop/opengl_api_define/android-7.1.2_r1/wrapperDir";
    std::string encoderDir = wrapperDir;
    std::string decoderDir = wrapperDir;
    std::string inDir = "/home/dengtao/Desktop/opengl_api_define/android-7.1.2_r1/";
    std::string baseName = "renderControl";
    ApiGen apiEntries(baseName);

    // init types;
    // std::string typesFilename = inDir + "/" + baseName + TYPES_EXTENTION;
    std::string typesFilename = "/home/dengtao/Desktop/opengl_api_define/android-7.1.2_r1/gles.types";
    if (TypeFactory::instance()->initFromFile(typesFilename) < 0) {
        fprintf(stderr, "missing or error reading types file: %s...ignored\n", typesFilename.c_str());
    }

    // std::string filename = inDir + "/" + baseName + SPEC_EXTENSION;
    std::string filename = "/home/dengtao/Desktop/opengl_api_define/android-7.1.2_r1/renderControl.in";
    if (apiEntries.readSpec(filename,ApiGen::CLIENT_SIDE) < 0) {
        perror(filename.c_str());
        return BAD_SPEC_FILE;
    }

    bool generateAttributesTemplate = false;
    if (generateAttributesTemplate) {
        apiEntries.genAttributesTemplate(inDir + "/" + baseName + ATTRIB_EXTENSION);
        exit(0);
    }

    // std::string attribFileName = inDir + "/" + baseName + ATTRIB_EXTENSION;
    std::string attribFileName = "/home/dengtao/Desktop/opengl_api_define/android-7.1.2_r1/renderControl.attrib";
    if (apiEntries.readAttributes(attribFileName) < 0) {
        perror(attribFileName.c_str());
        fprintf(stderr, "failed to parse attributes\n");
        exit(1);
    }

    if (encoderDir.size() != 0) {

        apiEntries.genOpcodes(encoderDir + "/" + baseName + "_opcodes.h");
        apiEntries.genContext(encoderDir + "/" + baseName + "_client_context.h", ApiGen::CLIENT_SIDE);
        apiEntries.genContextImpl(encoderDir + "/" + baseName + "_client_context.cpp", ApiGen::CLIENT_SIDE);

        apiEntries.genProcTypes(encoderDir + "/" + baseName + "_client_proc.h", ApiGen::CLIENT_SIDE);
        apiEntries.genFuncTable(encoderDir + "/" + baseName + "_ftable.h", ApiGen::CLIENT_SIDE);

        apiEntries.genEntryPoints(encoderDir + "/" + baseName + "_entry.cpp", ApiGen::CLIENT_SIDE);
        apiEntries.genEncoderHeader(encoderDir + "/" + baseName + "_enc.h");
        apiEntries.genEncoderImpl(encoderDir + "/" + baseName + "_enc.cpp");
        apiEntries.genTypeFile(encoderDir + "/" + baseName + "_types.h",ApiGen::CLIENT_SIDE);
    }

    if (decoderDir.size() != 0) {
        apiEntries.genOpcodes(decoderDir + "/" + baseName + "_opcodes.h");
        apiEntries.genProcTypes(decoderDir + "/" + baseName + "_server_proc.h", ApiGen::SERVER_SIDE);
        apiEntries.genContext(decoderDir + "/" + baseName + "_server_context.h", ApiGen::SERVER_SIDE);
        apiEntries.genContextImpl(decoderDir + "/" + baseName + "_server_context.cpp", ApiGen::SERVER_SIDE);
        apiEntries.genDecoderHeader(decoderDir + "/" + baseName + "_dec.h");
        apiEntries.genDecoderImpl(decoderDir + "/" + baseName + "_dec.cpp");
        apiEntries.genTypeFile(decoderDir + "/" + baseName + "_types.h",ApiGen::SERVER_SIDE);
    }

    if (wrapperDir.size() != 0) {
        if (TypeFactory::instance()->initFromFile(typesFilename) < 0) {
            fprintf(stderr, "missing or error reading types file: %s...ignored\n", typesFilename.c_str());
        }
        filename = "/home/dengtao/Desktop/opengl_api_define/android-7.1.2_r1/renderControl.in";
        if (apiEntries.readSpec(filename,ApiGen::WRAPPER_SIDE) < 0){
            perror(filename.c_str());
            return BAD_SPEC_FILE;
        }
        apiEntries.genProcTypes(wrapperDir + "/" + baseName + "_wrapper_proc.h", ApiGen::WRAPPER_SIDE);
        apiEntries.genContext(wrapperDir + "/" + baseName + "_wrapper_context.h", ApiGen::WRAPPER_SIDE);
        apiEntries.genContextImpl(wrapperDir + "/" + baseName + "_wrapper_context.cpp", ApiGen::WRAPPER_SIDE);
        apiEntries.genEntryPoints(wrapperDir + "/" + baseName + "_wrapper_entry.cpp", ApiGen::WRAPPER_SIDE);
        apiEntries.genTypeFile(wrapperDir + "/" + baseName + "_types.h",ApiGen::WRAPPER_SIDE);
    }

#ifdef DEBUG_DUMP
    int withPointers = 0;
    printf("%d functions found\n", int(apiEntries.size()));
    for (int i = 0; i < apiEntries.size(); i++) {
        if (apiEntries[i].hasPointers()) {
            withPointers++;
            apiEntries[i].print();
        }
    }
    fprintf(stdout, "%d entries has poitners\n", withPointers);
#endif
}
// int main(int argc, char *argv[])
// {
//     std::string encoderDir = "/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/android.in/encoderDir";
//     std::string decoderDir = "/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/firefly-rk3288/external/emugen.tools/android.in/decoderDir";
//     std::string wrapperDir = "/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/android.in/wrapperDir";
//     encoderDir = wrapperDir;
//     decoderDir = wrapperDir;
//     std::string inDir = "/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/android.in/";
//     std::string baseName = "gles";
//     ApiGen apiEntries(baseName);

//     // init types;
//     std::string typesFilename = "/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/android.in/gles/gles.types";

//     if (TypeFactory::instance()->initFromFile(typesFilename) < 0) {
//         fprintf(stderr, "missing or error reading types file: %s...ignored\n", typesFilename.c_str());
//     }

//     std::string filename = "/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/android.in/gles/gles.in";
//     if (apiEntries.readSpec(filename,ApiGen::CLIENT_SIDE) < 0) {
//         perror(filename.c_str());
//         return BAD_SPEC_FILE;
//     }

//     bool generateAttributesTemplate = false;
//     if (generateAttributesTemplate) {
//         apiEntries.genAttributesTemplate(inDir + "/" + baseName + ATTRIB_EXTENSION);
//         exit(0);
//     }

//     std::string attribFileName = "/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/android.in/gles/gles.attrib";
//     if (apiEntries.readAttributes(attribFileName) < 0) {
//         perror(attribFileName.c_str());
//         fprintf(stderr, "failed to parse attributes\n");
//         exit(1);
//     }

//     if (encoderDir.size() != 0) {

//         apiEntries.genOpcodes(encoderDir + "/" + baseName + "_opcodes.h");
//         apiEntries.genContext(encoderDir + "/" + baseName + "_client_context.h", ApiGen::CLIENT_SIDE);
//         apiEntries.genContextImpl(encoderDir + "/" + baseName + "_client_context.cpp", ApiGen::CLIENT_SIDE);

//         apiEntries.genProcTypes(encoderDir + "/" + baseName + "_client_proc.h", ApiGen::CLIENT_SIDE);
//         apiEntries.genFuncTable(encoderDir + "/" + baseName + "_ftable.h", ApiGen::CLIENT_SIDE);

//         apiEntries.genEntryPoints(encoderDir + "/" + baseName + "_entry.cpp", ApiGen::CLIENT_SIDE);
//         apiEntries.genEncoderHeader(encoderDir + "/" + baseName + "_enc.h");
//         apiEntries.genEncoderImpl(encoderDir + "/" + baseName + "_enc.cpp");
//         apiEntries.genTypeFile(encoderDir + "/" + baseName + "_types.h",ApiGen::CLIENT_SIDE);
//     }

//     if (decoderDir.size() != 0) {
//         apiEntries.genOpcodes(decoderDir + "/" + baseName + "_opcodes.h");
//         apiEntries.genProcTypes(decoderDir + "/" + baseName + "_server_proc.h", ApiGen::SERVER_SIDE);
//         apiEntries.genContext(decoderDir + "/" + baseName + "_server_context.h", ApiGen::SERVER_SIDE);
//         apiEntries.genContextImpl(decoderDir + "/" + baseName + "_server_context.cpp", ApiGen::SERVER_SIDE);
//         apiEntries.genDecoderHeader(decoderDir + "/" + baseName + "_dec.h");
//         apiEntries.genDecoderImpl(decoderDir + "/" + baseName + "_dec.cpp");
//         apiEntries.genTypeFile(decoderDir + "/" + baseName + "_types.h",ApiGen::SERVER_SIDE);
//     }

//     if (wrapperDir.size() != 0) {
//         if (TypeFactory::instance()->initFromFile(typesFilename) < 0) {
//             fprintf(stderr, "missing or error reading types file: %s...ignored\n", typesFilename.c_str());
//         }
//         filename = "/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/android.in/entries.in";
//         if (apiEntries.readSpec(filename,ApiGen::WRAPPER_SIDE) < 0){
//             perror(filename.c_str());
//             return BAD_SPEC_FILE;
//         }
//         if (access("/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/android.in/entries.attrib",0)!=R_OK){
//             apiEntries.genAttributesTemplate("/home/dengtao/Desktop/firefly-rk3288/external/emugen.tools/android.in/entries.attrib");  
//         }
//         apiEntries.genProcTypes(wrapperDir + "/" + baseName + "_wrapper_proc.h", ApiGen::WRAPPER_SIDE);
//         apiEntries.genContext(wrapperDir + "/" + baseName + "_wrapper_context.h", ApiGen::WRAPPER_SIDE);
//         apiEntries.genContextImpl(wrapperDir + "/" + baseName + "_wrapper_context.cpp", ApiGen::WRAPPER_SIDE);
//         apiEntries.genEntryPoints(wrapperDir + "/" + baseName + "_wrapper_entry.cpp", ApiGen::WRAPPER_SIDE);
//         apiEntries.genTypeFile(wrapperDir + "/" + baseName + "_types.h",ApiGen::WRAPPER_SIDE);
//     }
// #ifdef DEBUG_DUMP
//     int withPointers = 0;
//     printf("%d functions found\n", int(apiEntries.size()));
//     for (int i = 0; i < apiEntries.size(); i++) {
//         if (apiEntries[i].hasPointers()) {
//             withPointers++;
//             apiEntries[i].print();
//         }
//     }
//     fprintf(stdout, "%d entries has poitners\n", withPointers);
// #endif
// }
#endif
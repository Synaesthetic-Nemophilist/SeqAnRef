//
// Created by Jerry Kougianos on 29/06/2018.
//
/**
http://seqan.readthedocs.io/en/master/Tutorial/GettingStarted/ParsingCommandLineArguments.html
 **/

#include <iostream>

#include <seqan/arg_parse.h>


struct ModifyStringOptions {
    unsigned period;
    unsigned rangeBegin, rangeEnd;
    bool toUppercase;
    bool toLowercase;
    seqan::CharString text;

    ModifyStringOptions() :
            period(1), rangeBegin(0), rangeEnd(0), toUppercase(false),
            toLowercase(false) {}
};


seqan::ArgumentParser::ParseResult parseCommandLine(ModifyStringOptions &options, int argc, char const **argv) {
    // Setup ArgumentParser
    seqan::ArgumentParser parser("modify_string");
    // Setup doc
    seqan::setShortDescription(parser, "String Modifier");
    seqan::setVersion(parser, "1.0");
    seqan::setDate(parser, "July 2018");
    seqan::addUsageLine(parser,
                        R"([\fIOPTIONS\fP] "\fITEXT\fP")");
    seqan::addDescription(parser,
                          "This program allows simple character modifications to "
                          "each i-th character.");

    seqan::addSection(parser, "Modification Options");

    // We require one argument.
    addArgument(parser, seqan::ArgParseArgument(
            seqan::ArgParseArgument::STRING, "TEXT"));

    // Define options
    addOption(parser, seqan::ArgParseOption("i",
                                            "period",
                                            "Period to use for the index",
                                            seqan::ArgParseArgument::INTEGER,
                                            "INT"));
    setMinValue(parser, "period", "1");
    setDefaultValue(parser, "period", "1");

    // Since this option has no type defined, it behaves as a flag (e.g. --uppercase)
    addOption(parser, seqan::ArgParseOption("U",
                                            "uppercase",
                                            "Select to-uppercase as operation"));
    addOption(parser, seqan::ArgParseOption("L",
                                            "lowercase",
                                            "Select to-lowercase as operation"));

    seqan::addTextSection(parser, "Examples");

    seqan::addListItem(parser,
                       R"(\fBmodify_string\fP \fB-U\fP \fIveryverylongword\fP)",
                       "Print upper case version of \"veryverylongword\"");
    seqan::addListItem(parser,
                       R"(\fBmodify_string\fP \fB-L\fP \fB-i\fP \fI3\fP \fIveryverylongword\fP)",
                       "Print \"veryverylongword\" with every third character "
                       "converted to upper case.");

    // Parse command line.
    seqan::ArgumentParser::ParseResult res = parse(parser, argc, argv);

    // Only extract  options if the program will continue after parseCommandLine()
    if (res != seqan::ArgumentParser::PARSE_OK)
        return res;

    // Extract option values and print them.
    getOptionValue(options.period, parser, "period");
    options.toUppercase = isSet(parser, "uppercase");
    options.toLowercase = isSet(parser, "lowercase");
    getArgumentValue(options.text, parser, 0);

    // If both to-uppercase and to-lowercase were selected then this is an error.
    if (options.toLowercase && options.toUppercase) {
        std::cerr << "ERROR: You cannot specify both to-uppercase and to-lowercase!\n";
        return seqan::ArgumentParser::PARSE_ERROR;
    }

    return seqan::ArgumentParser::PARSE_OK;;
}

seqan::CharString modifyString(seqan::CharString const &text, ModifyStringOptions const &options) {
    seqan::CharString result;

    if (options.toLowercase) {
        for (unsigned i = 0; i < length(text); ++i) {
            if (i % options.period == 0u)
                appendValue(result, tolower(text[i]));
            else
                appendValue(result, text[i]);
        }
    } else {
        for (unsigned i = 0; i < length(text); ++i) {
            if (i % options.period == 0u)
                appendValue(result, toupper(text[i]));
            else
                appendValue(result, text[i]);
        }
    }

    return result;
}


int main(int argc, char const **argv) {
    // Parse the command line.
    ModifyStringOptions options;
    seqan::ArgumentParser::ParseResult res = parseCommandLine(options, argc, argv);

    // If parsing was not successful then exit with code 1 if there were errors.
    // Otherwise, exit with code 0 (e.g. help was printed).
    if (res != seqan::ArgumentParser::PARSE_OK)
        return res == seqan::ArgumentParser::PARSE_ERROR;

    std::cout << modifyString(options.text, options) << '\n';

    return 0;
}
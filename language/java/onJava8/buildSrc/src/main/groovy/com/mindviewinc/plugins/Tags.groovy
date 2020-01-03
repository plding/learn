package com.mindviewinc.plugins

class Tags {
    Boolean hasMainMethod = false
    Boolean willNotCompile = false
    Boolean excludeFromTravisCI = false
    Boolean excludeFromAppveyorCI = false
    Boolean excludeFromCI = false
    Boolean lowLevelAppendix = false
    Boolean throwsException = false
    Boolean errorOutputExpected = false
    Boolean excludeFromGradle = false
    Boolean ignoreOutput = false // This tag isn't used in the build...
    String fileRoot
    String mainClass
    String javaCmd = null
    List<String> args = []
    List<String> jVMArgs = []
    String javap = null
    String runFirst = null
    String outputLine = null
    private String block
    def Tags(File file) {
        block = file.text
        hasMainMethod = block.contains('main(String[] args)')
        def firstLine = block.substring(0, block.indexOf("\n"))
        fileRoot = (firstLine.split("/")[-1] - ".java").trim() // Remove \r if it exists
        mainClass = fileRoot
        javaCmd = extract('java')
        if(javaCmd) {
            def pieces = javaCmd.split()
            mainClass = pieces[0]
            if(pieces.size() > 1)
                for(p in pieces[1..-1])
                    if(p.startsWith("-"))
                        jVMArgs << p
                    else
                        args << p
        }
        willNotCompile = hasTag('WillNotCompile')
        excludeFromTravisCI = hasTag('ExcludeFromTravisCI')
        excludeFromAppveyorCI = hasTag('ExcludeFromAppveyorCI')
        excludeFromCI = hasTag('ExcludeFromCI')
        lowLevelAppendix = firstLine.contains("// lowlevel/")
        throwsException = hasTag('ThrowsException')
        errorOutputExpected = hasTag('ErrorOutputExpected')
        excludeFromGradle = hasTag('ExcludeFromGradle')
        ignoreOutput = hasTag('IgnoreOutput')
        javap = extract('javap') // Includes only arguments to command
        runFirst = extract('RunFirst:')
        outputLine = extractOutputLine()
    }
    private def hasTag(String marker) {
        return block.contains("// {" + marker + "}")
    }
    def extractOutputLine() {
        def matcher = (block =~ /(?m)^(\/\* Output:.*)$/)
        if (matcher) {
            return matcher[0][1]
        } else {
            return null
        }
    }
    private def extract(String marker) {
        // Assume some whitespace is after marker
        if(!block.contains("// {${marker} "))
            return null
        def matcher = (block =~ /\/\/ \{${marker}\s+([^}]+)/)
        if (matcher) {
            def matched = matcher[0][1].trim()
            return matched.replaceAll("\n?//", "")
        } else {
            println "Searching for: " + matcher
            println block
            System.exit(1)
        }
    }
    public boolean hasTags() {
        return willNotCompile ||
        excludeFromTravisCI ||
        excludeFromAppveyorCI ||
        excludeFromCI ||
        throwsException ||
        errorOutputExpected ||
        excludeFromGradle ||
        ignoreOutput ||
        javaCmd ||
        args ||
        jVMArgs ||
        javap ||
        runFirst
    }
    public String toString() {
        String result = ""
        block.eachLine{ ln ->
            if(ln.startsWith("//") || ln.startsWith("package "))
                result += ln + "\n"
        }
        """
        hasMainMethod
        willNotCompile
        excludeFromTravisCI
        excludeFromAppveyorCI
        excludeFromCI
        throwsException
        errorOutputExpected
        excludeFromGradle
        ignoreOutput
        fileRoot
        mainClass
        javaCmd
        args
        jVMArgs
        javap
        runFirst
        """.split().each { str ->
            if(this[str])
                result += str + ": " + this[str] + "\n"
        }
        result
    }
}

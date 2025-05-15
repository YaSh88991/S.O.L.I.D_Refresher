// ===== SRP Violation Example =====

#include <fstream>
#include <string>

class Report {
public:
    Report(const std::string& data)
      : content(data)
    {}

    // Responsibility #1: formatting
    void formatHTML() {
        content = "<html><body>" + content + "</body></html>";
    }

    // Responsibility #2: file I/O
    void generateFile(const std::string& filename) {
        std::ofstream ofs(filename);
        ofs << content;
    }

private:
    std::string content;
};

int main() {
    Report rpt("Quarterly earnings: $1M");

    // Both concerns live in the same class:
    rpt.formatHTML();
    rpt.generateFile("report.html");
    return 0;
}


// ===== The same example Refactored to a SRP-Compliant example =====

#include <fstream>
#include <string>

// 1) Single responsibility: formatting text
class HTMLFormatter {
public:
    static std::string format(const std::string& raw) {
        return "<html><body>" + raw + "</body></html>";
    }
};

// 2) Single responsibility: writing files
class FileWriter {
public:
    static void write(const std::string& filename,
                      const std::string& data)
    {
        std::ofstream ofs(filename);
        ofs << data;
    }
};

// 3) Report now has only one job: hold data and coordinate
class Report {
public:
    explicit Report(std::string data)
      : content(std::move(data))
    {}

    void saveAsHTML(const std::string& filename) const {
        auto html = HTMLFormatter::format(content);
        FileWriter::write(filename, html);
    }

private:
    std::string content;
};

int main() {
    Report rpt("Quarterly earnings: $1M");

    // SRP honored: Report delegates formatting & I/O
    rpt.saveAsHTML("report.html");
    return 0;
}

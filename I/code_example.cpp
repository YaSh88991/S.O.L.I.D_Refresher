// ===== ISP Violation Example =====

// A fat “INotifier” interface forces every notifier to implement all methods,
// even if they only need one. Unused methods are left empty or throw.

#include <iostream>
#include <stdexcept>
#include <string>

// Fat interface
class INotifier {
public:
    virtual ~INotifier() = default;
    virtual void sendEmail(const std::string& msg) = 0;
    virtual void sendSMS(const std::string& msg)   = 0;
    virtual void sendPush(const std::string& msg)  = 0;
};

// Email-only notifier must stub out SMS and Push
class EmailNotifier : public INotifier {
public:
    void sendEmail(const std::string& msg) override {
        std::cout << "[Email] " << msg << "\n";
    }
    void sendSMS(const std::string&) override {
        // Not supported—throw or no-op
        throw std::logic_error("EmailNotifier cannot send SMS");
    }
    void sendPush(const std::string&) override {
        throw std::logic_error("EmailNotifier cannot send Push notifications");
    }
};

// SMS-only notifier must stub out others
class SMSNotifier : public INotifier {
public:
    void sendEmail(const std::string&) override {
        throw std::logic_error("SMSNotifier cannot send Email");
    }
    void sendSMS(const std::string& msg) override {
        std::cout << "[SMS] " << msg << "\n";
    }
    void sendPush(const std::string&) override {
        throw std::logic_error("SMSNotifier cannot send Push notifications");
    }
};

// Client code wants to send a notification by email
void notifyUserEmail(INotifier& notifier, const std::string& msg) {
    notifier.sendEmail(msg);  // but EmailNotifier.sendSMS/sendPush are irrelevant
}

int main() {
    EmailNotifier email;
    notifyUserEmail(email, "Your report is ready.");
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------


// ===== Refactoring to a ISP-Compliant Example =====
// Split into three small interfaces so each notifier implements only what it needs.

#include <iostream>
#include <string>

// Segregated interfaces
class IEmailNotifier {
public:
    virtual ~IEmailNotifier() = default;
    virtual void sendEmail(const std::string& msg) = 0;
};

class ISMSNotifier {
public:
    virtual ~ISMSNotifier() = default;
    virtual void sendSMS(const std::string& msg) = 0;
};

class IPushNotifier {
public:
    virtual ~IPushNotifier() = default;
    virtual void sendPush(const std::string& msg) = 0;
};

// Concrete implementations implement only their interface
class EmailNotifier2 : public IEmailNotifier {
public:
    void sendEmail(const std::string& msg) override {
        std::cout << "[Email] " << msg << "\n";
    }
};

class SMSNotifier2 : public ISMSNotifier {
public:
    void sendSMS(const std::string& msg) override {
        std::cout << "[SMS] " << msg << "\n";
    }
};

class PushNotifier2 : public IPushNotifier {
public:
    void sendPush(const std::string& msg) override {
        std::cout << "[Push] " << msg << "\n";
    }
};

// Clients depend on exactly the interface they use
void notifyByEmail(IEmailNotifier& notifier, const std::string& msg) {
    notifier.sendEmail(msg);
}

void notifyBySMS(ISMSNotifier& notifier, const std::string& msg) {
    notifier.sendSMS(msg);
}

void notifyByPush(IPushNotifier& notifier, const std::string& msg) {
    notifier.sendPush(msg);
}

int mainCompliant() {
    EmailNotifier2 email;
    SMSNotifier2   sms;
    PushNotifier2  push;

    notifyByEmail(email, "Your report is ready.");
    notifyBySMS(sms,     "Your OTP code is 123456.");
    notifyByPush(push,   "You have a new friend request.");

    return 0;
}

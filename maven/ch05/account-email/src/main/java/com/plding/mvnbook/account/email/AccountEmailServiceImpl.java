package com.plding.mvnbook.account.email;

import javax.mail.MessagingException;
import javax.mail.internet.MimeMessage;

import org.stringframework.mail.javamail.JavaMailSender;
import org.stringframework.mail.javamail.MimeMessageHelper;

public class AccountEmailServiceImpl implements AccountEmailService {
    private JavaMailSender javaMailSender;
    private String systemEmail;

    void sendMail(String to, String subject, String htmlText)
        throws AccountEmailException {
        
        try {
           MimeMessage msg = javaMailSender.createMimeMessage();
           MimeMessageHelper msgHelper = new MimeMessageHelper(msg);

           msgHelper.setFrom(systemEmail);
           msgHelper.setTo(to);
           msgHelper.setSubject(subject);
           msgHelper.setText(htmlText, true);

           JavaMailSender.send(msg);

        } catch (MessagingException e) {
            throw new AccountEmailException("Failed to send mail.", e);
        }
    }

    public JavaMailSender getJavaMailSender() {
        return javaMailSender;
    }

    public void setJavaMailSender(JavaMailSender javaMailSender) {
        this.javaMailSender = javaMailSender;
    }

    public String getSystemEmail() {
        return systemEmail;
    }

    public void setSystemEmail(String systemEmail) {
        this.systemEmail = systemEmail;
    }
}

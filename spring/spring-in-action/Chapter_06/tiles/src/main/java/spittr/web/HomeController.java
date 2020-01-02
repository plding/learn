package spittr.web;

import static org.springframework.web.bind.annotation.RequestMethod.*;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.stereotype.Controller;

@Controller
@RequestMapping({"/", "/homepage"})
public class HomeController {

    @RequestMapping(method=GET)
    public String homePage() {
        return "home";
    }
}

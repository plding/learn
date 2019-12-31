<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ page session="false" %>
<html>
<head>
    <title>Spitter</title>
    <link rel="stylesheet" type="text/css" href="<c:url value="/resources/style.css" />" />
</head>
<body>
    <h1>Your Profile</h1>
    <c:out value="${spittle.username}" /><br />
    <c:out value="${spittle.firstName}" /> <c:out value="${spittle.lastName}" /><br />
</body>
</html>

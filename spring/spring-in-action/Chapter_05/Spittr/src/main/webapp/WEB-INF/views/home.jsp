<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ page session="false" %>
<html>
<head>
    <title>Spitter</title>
    <link ref="stylesheet" type="text/css" href="<c:url value="/resource/style.css" />" />
</head>
<body>
    <h1>Welcome to Spitter</h1>
    
    <a href="<c:url value="/spittles" />">Spittles</a> |
    <a href="<c:url value="/spitter/register" />">Register</a>
</body>
</html>

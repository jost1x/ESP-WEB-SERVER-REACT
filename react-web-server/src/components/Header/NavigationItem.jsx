import { Link } from "react-router-dom"


export default function NavigationItem({ path, text }) {
    return (
        <Link to={path} className="button">{text}</Link>
    )
}
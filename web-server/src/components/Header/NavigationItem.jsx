export default function NavigationItem({ path, text }) {
    return (
        <a href={path} className="button">{text}</a>
    )
}
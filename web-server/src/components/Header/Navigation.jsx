import NavigationItem from "./NavigationItem";

export default function Navigation() {
    return (<>
        <NavigationItem path="./" text="Home" />
        <NavigationItem path="./settings" text="Ajustes" />
    </>
    )
}